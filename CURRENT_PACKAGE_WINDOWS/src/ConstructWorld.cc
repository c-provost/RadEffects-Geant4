#include "ConstructWorld.hh"
#include "DetectorMessenger.hh"
#include <cmath>


MyDetectorConstruction::MyDetectorConstruction()
{
    DefineMaterials();
    // Half dimensions of the world volume
    xWorld = 10 * cm; 
    yWorld = 10 * cm;
    zWorld = 40 * cm;
}

MyDetectorConstruction::~MyDetectorConstruction()
{ }    

void MyDetectorConstruction::DefineMaterials()
{
    G4NistManager* nist = G4NistManager::Instance();

    Aluminum      = nist->FindOrBuildMaterial("G4_Al");
    Gold          = nist->FindOrBuildMaterial("G4_Au");
    Tungsten      = nist->FindOrBuildMaterial("G4_W");
    Steel         = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
    polyStyrene   = nist->FindOrBuildMaterial("G4_POLYSTYRENE");
    Silicon       = nist->FindOrBuildMaterial("G4_Si");
    Ceramic       = nist->FindOrBuildMaterial("G4_ALUMINUM_OXIDE");
    SiO2          = nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
    plastic       = nist->FindOrBuildMaterial("G4_POLYVINYL_CHLORIDE");
    poly          = nist->FindOrBuildMaterial("G4_POLYACRYLONITRILE");


    G4double a = 1.01*g/mole;
    G4double pressure = 1.e-19 * pascal;
    G4double temperature = 0.1*kelvin;
    G4double density = CLHEP::universe_mean_density;
    //worldMaterial = new G4Material("Vacuum", 1., a, density, kStateGas, temperature, pressure);
    worldMaterial = nist->FindOrBuildMaterial("G4_AIR");
    worldMaterial->SetName("AIR");
}

G4VPhysicalVolume* MyDetectorConstruction::Construct()
{

    // ************************************************************************************************
    // Variable Farm. In here is where all the necessary variables for the construction of the geometry
    // are initialized to their default values. These, in theory, should be able to be adjusted with UI
    // command (my current project)                             -Conrad Provost •Monday, April 29, 2024
    // ************************************************************************************************

        // Default parameters for the ConstructionGeometry
    // Dimensions according to MIL-STD-1835D for package construction
    //                    ↓ converting inches to centimeters      
    G4double D = 1.490 * 2.54 * cm;
    G4double E =  .550 * 2.54 * cm;
    G4double A =  .232 * 2.54 * cm;
    G4double Q =  .060 * 2.54 * cm;

    // Height of the package chunk
    height = (A-Q)/2;

    // Cavity Dimensions, as measured by Rob and Myself.
    cavD = .015625 * 2.54 * cm;   // 1/64 of an inch.
    cavL = 27 * cavD;
    cavW = 22 * cavD;

    // Wafer Dimensions - Accessed from shotty internet articles.
    waferdepth = 500 * um;
    waferlength = .5 * cm;
    waferwidth = .3 * cm;

    xPosWafer = (3.*cm);
    yPosWafer = (3.*cm);
    zPosWafer = -1*(height/2 - cavD + waferdepth/2);

    // Pack Chunk Dimensions
    packChunkwidth = .8 * cm;
    packChunklength = .6 * cm;

    // Bottom information
    bottompos = G4ThreeVector(3.0 * cm, 3.0 * cm, zPosWafer);

    // Lid information
    lidpos = G4ThreeVector(0., 0., (height-cavD)/2);

    // Overlayer information
    passlayerthickness = 1500*um;
    passlayerxpos = 3. * cm;
    passlayerypos = 3.*cm;
    passlayerzpos = -1*(height/2 - cavD + waferdepth + passlayerthickness/2);
    passlayerpos = G4ThreeVector(passlayerxpos, passlayerypos, passlayerzpos);

    // ********** END OF FARM *********** END OF FARM *********** END OF FARM ************ END OF FARM *********** // 


    // Added these for quasi-automation of simulation configurations. 
    lidpresence = false;
    bottompresence = false;
    alboxpresence  = true;
    overlayerpresence = true;

    // This is the world volume. Constructed of air, it is the "world" in which our physics
    // processes take place. Each input parameter is the half-length of total dimension.
    solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);
    logicalWorld = new G4LogicalVolume(solidWorld, worldMaterial, "logicalWorld");
    physicalWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicalWorld, "physicalWorld", 0, false, 0, true);


    // ********************
    // Building the package
    // ********************

    G4cout <<  "The thickness is " << height / cm << G4endl;


    mainBody = new G4Box("packChunk", packChunkwidth/2, packChunklength/2, height/2);
    cavity = new G4Box("Cav1", cavL/2, cavW/2, cavD/2);
    
    Bot = new G4SubtractionSolid("Bot", mainBody, cavity, 0, G4ThreeVector(3.0 *cm, 3.0*cm, -1*(height-cavD)/2));
    Lid = new G4SubtractionSolid("Lid", mainBody, cavity, 0, G4ThreeVector(0., 0., (height-cavD)/2));

    logicBot = new G4LogicalVolume(Bot, Ceramic, "logicBot");
    logicLid = new G4LogicalVolume(Lid, Ceramic, "logicLid");

    if (bottompresence){ physBot = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicBot, "physBot", logicalWorld, false, 0, true); }
    if (lidpresence) {   physLid = new G4PVPlacement(0, G4ThreeVector(0., 0., -1*(height + cavD + 650 * um)), logicLid, "physLid", logicalWorld, false, 0, true); }
    

    // ********************************
    // Constructing the Silicon Wafer *
    // ********************************

    // the silicon wafer corresponding to the chip in the package. The dummy dimensions that create the outline.
    // To be filled with 20 slices that fill the entirety of the volume. I believe there is way to do this with 
    // G4ParameterisedVolume, but that is a project for another day. *-Conrad Jan. 9, 2024*

    // 
    G4ThreeVector waferPos = G4ThreeVector(xPosWafer, yPosWafer, zPosWafer);
    wafer = new G4Box("wafer", waferlength/2, waferwidth/2, waferdepth/2);
    logwafer = new G4LogicalVolume(wafer, Silicon, "logWafer");

    
    // *************************************************
    // Scoring Volumes with the wafer as a mother volume
    // *************************************************
    numslices = 20;
    sliceDepth = waferdepth/numslices;
    G4Material* SliceMaterial = Silicon;

    G4cout << "The Slice depth is " << sliceDepth / um << " um" << G4endl;

    // Basic Slice Shape for the Wafer. 
    Slice_Stub = new G4Box("Slice_Stub", waferlength/2, waferwidth/2, sliceDepth/2);

    // The start Z position for scoringvolume placment. (within the wafer)
    startZpos = -1 * (waferdepth/2) + sliceDepth/2;

    for(int i = 0; i < numslices; i++)
    {  
        G4String logtitle;
        // Creating the names for the layers.
        if (i < 9) { logtitle  = "logSlice_0"  + std::to_string(i+1); }

        else       { logtitle = "logSlice_"  + std::to_string(i+1); }

        // Creating The Logical Volumes
        LogList[i] = new G4LogicalVolume(Slice_Stub, SliceMaterial, logtitle);
    }

    // Placing the PhysWafer Object
    ConstructWafer(xPosWafer, yPosWafer, zPosWafer, true);


    // ***********************************
    // Construction of Overlayers on Wafer
    // ***********************************

    G4Material* passMaterial = Ceramic;
    passLayer = new G4Box("PassLayer", waferlength/2, waferwidth/2, passlayerthickness/2);
    passLayerlog = new G4LogicalVolume(passLayer, passMaterial, "passLayerlog");
    if (overlayerpresence)
        { passLayerphys = new G4PVPlacement(0, passlayerpos, passLayerlog, "passLayerphys", logicalWorld, false, 0, true); }


    // *******************************************
    // Construction of Aluminum Box around package
    // *******************************************
    G4Box *AlChunk = new G4Box("Chunk", xWorld/2, yWorld/2, xWorld/2);
    G4Box *AirChunk = new G4Box("Air", xWorld/2 - .8 * mm, xWorld/2 - .8*mm, xWorld/2 - .8*mm);

    AlBox = new G4SubtractionSolid("Box", AlChunk, AirChunk, 0, G4ThreeVector(0., 0., 0.));
    AlBox_log = new G4LogicalVolume(AlBox, Aluminum, "LogBox");
    if (alboxpresence) { AlBox_phys = new G4PVPlacement(0, G4ThreeVector(0., 0., 3.75 * cm), AlBox_log, "physBox", logicalWorld, false, 0, true); }
    

    // ***********************************************************
    // Construction of Silicon 'backscattering' chunk behind wafer
    // ***********************************************************
    G4double chunkdepth = 1000 * um;
    silChunk = new G4Box("SilChunkBox", waferlength/2, waferwidth/2, chunkdepth/2);
    silChunk_log = new G4LogicalVolume(silChunk, Silicon, "SilChunk");

    G4double chunkZpos = -1*(height/2 - cavD + waferdepth/2) + waferdepth/2 + chunkdepth/2;
    silChunk_phys = new G4PVPlacement(0, G4ThreeVector(3.0*cm, 3.0*cm, chunkZpos), silChunk_log, "silChunk_phys", logicalWorld, false, 0, true);


    // ************
    // Data volumes
    // ************
    fbottom = logicBot; 
    flid = logicLid;
    fOverLayer = passLayerlog;

    return physicalWorld;
}

void MyDetectorConstruction::ConstructWafer(G4double xpos, G4double ypos, G4double zpos, G4bool initialplacement)
{   
    // Deleting these members if they already exist
    if(physwafer)     { delete physwafer; }
    
    // Upates the xposition, yposition, and zposition of the wafer if not the NULL code (1010101)
    // There's got to be a better way to set defaults, but keyword arg funcitionality does not 
    // match that of python, which I am trying to emulate here. - CP May 4, 2024

    // Updating the wafer positional arguments, calculating the change compared to previous versions.
    G4double deltax, deltay, deltaz;
    if(xpos != 1010101) {deltax = xpos - xPosWafer; xPosWafer = xpos;}
        else { deltax = 0.; }
    if(ypos != 1010101) {deltay = ypos - yPosWafer; yPosWafer = ypos; }
        else { deltay = 0.; }
    if(zpos != 1010101) {deltaz = zpos - zPosWafer; zPosWafer = zpos; }
        else { deltaz = 0.; }
    
    // Asking if this is the first time placing the volume. If not, makes sure everything jives well. 
    if( !initialplacement )
    {
        if(overlayerpresence)
        {
            ConstructOverLayer(passlayerxpos + deltax, passlayerypos + deltay, passlayerzpos + deltaz);
        }
    }

    
    // Updating the wafer position in accordance with input parameters to the construct function
    G4ThreeVector waferPosition = G4ThreeVector(xPosWafer, yPosWafer, zPosWafer);
    physwafer = new G4PVPlacement(0, waferPosition, logwafer, "physwafer", logicalWorld, false, 0, true);
    ConstructScoringLayers(numslices, startZpos, sliceDepth);
    
}
void MyDetectorConstruction::ConstructOverLayer(G4double xpos, G4double ypos, G4double zpos)
{   
    // Deleting if already exists. Prevents memory allocation issues.
    if(passLayerphys) { delete passLayerphys; }

    // Creating new three vector with input parameters for overlayer.
    G4ThreeVector position;
    position = G4ThreeVector(xpos, ypos, zpos);

    passLayerphys = new G4PVPlacement(0, position, passLayerlog, "passLayerphys", logicalWorld, false, 0, true);
}

void MyDetectorConstruction::ConstructScoringLayers(G4double numslices, G4double startZpos, G4double sliceDepth)
{
    // Method that builds the scoringlayer slices within the wafer. Must be called after wafer is placed. 
    for(int i = 0; i < numslices; i++)
    {  
        delete PhysList[i];
        G4String phystitle;
        // Creating the names for the layers.
        if (i < 9) { phystitle = "physSlice_0" + std::to_string(i+1); }

        else       { phystitle = "physSlice_" + std::to_string(i+1); }

        // Creating the Physical Volumes
        PhysList[i] = new G4PVPlacement(0, G4ThreeVector(0., 0., startZpos + i * sliceDepth), LogList[i], phystitle, logwafer, false, 0, true);
    }
}