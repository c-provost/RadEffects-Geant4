#include "ConstructWorld.hh"
#include "DetectorMessenger.hh"
#include <cmath>
#include "PackSensitiveDetector.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4SolidStore.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
    lvs = G4LogicalVolumeStore::GetInstance();
    pvs = G4PhysicalVolumeStore::GetInstance();
    DefineMaterials();
    // Half dimensions of the world volume
    xWorld = 10 * cm; 
    yWorld = 10 * cm;
    zWorld = 40 * cm;

    // Initializing the number of scoring volumes
    num_scoring = 20;

    // Initializing default scoring volume placement. 

        PhysList = std::vector<G4LogicalVolume*>(num_scoring, 0);

}

MyDetectorConstruction::~MyDetectorConstruction() { }   
 
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
    lead          = nist->FindOrBuildMaterial("G4_Pb");


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
    // command (my current project)                            -Conrad Provost • Monday, April 29, 2024
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

    // The initial positions of the wafer volume
    xPosWafer = (3.*cm);
    yPosWafer = (3.*cm);
    zPosWafer = -1*(height/2 - cavD + waferdepth/2);
    G4cout << "The intial z position of wafer is " << zPosWafer/cm << "cm" << G4endl;

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

    // ************************************************
    // User-defined booleans for package configurations 
    // ************************************************
        lidpresence = false;
        bottompresence = false;
        alboxpresence  = true;
        overlayerpresence = false;
        backscatterpresence = true;
        pbBoxpresence = true;
    // ********************************************************
    // Construction of World Volume - the Primary Mother Volume
    // ********************************************************
        // Each input is half length of total dimensions
        solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);
        logicalWorld = new G4LogicalVolume(solidWorld, worldMaterial, "logicalWorld");
        physicalWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicalWorld, "physicalWorld", 0, false, 0, true);
    // ********************
    // Building the package
    // ********************
        // Simplified geometry of lid and bottom layers for package, and the cavity within them.
        mainBody = new G4Box("packChunk", packChunkwidth/2, packChunklength/2, height/2);
        cavity = new G4Box("Cav1", cavL/2, cavW/2, cavD/2);
        // Putting the cavity into the body
        Bot = new G4SubtractionSolid("Bot", mainBody, cavity, 0, G4ThreeVector(3.0 *cm, 3.0*cm, -1*(height-cavD)/2));
        Lid = new G4SubtractionSolid("Lid", mainBody, cavity, 0, G4ThreeVector(0., 0., (height-cavD)/2));
        // Defining logical volumes for lid and bottom
        logicBot = new G4LogicalVolume(Bot, Ceramic, "logicBot");
        logicLid = new G4LogicalVolume(Lid, Ceramic, "logicLid");
        // Determing whether the user wants to actually include the lid and bottom (in accordance with booleans at top of routine)
        if (bottompresence){ physBot = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicBot, "physBot", logicalWorld, false, 0, true); }
        if (lidpresence) {   physLid = new G4PVPlacement(0, G4ThreeVector(0., 0., -1*(height + cavD + 650 * um)), logicLid, "physLid", logicalWorld, false, 0, true); }
    // ********************************
    // Constructing the Silicon Wafer *
    // ********************************
        // the silicon wafer corresponding to the chip in the package. The dummy dimensions that create the outline.
        // To be filled with 20 slices that fill the entirety of the volume. I believe there is way to do this with 
        // G4ParameterisedVolume, but that is a project for another day. *-Conrad Jan. 9, 2024*
        G4ThreeVector waferPos = G4ThreeVector(xPosWafer, yPosWafer, zPosWafer);
        wafer = new G4Box("wafer", waferlength/2, waferwidth/2, waferdepth/2);
        logwafer = new G4LogicalVolume(wafer, Silicon, "logWafer");
    // *************************************************
    // Scoring Volumes with the wafer as a mother volume
    // *************************************************
        sliceDepth = waferdepth/num_scoring;
        G4Material* SliceMaterial = Silicon;
        // Printing to terminal how thick each scoring layer is
        G4cout << "The Slice depth is " << sliceDepth / um << " um" << G4endl;

    // Basic Slice Shape for the Wafer. 
    ScoringSolid = new G4Box("ScoringSolid", waferlength/2, waferwidth/2, sliceDepth/2);
    ScoringLog = new G4LogicalVolume(ScoringSolid, SliceMaterial, "ScoringLog");

    // The start Z position for scoringvolume placment. (within the wafer)
    startZpos = -1 * (waferdepth/2) + sliceDepth/2;

    // Placing the PhysWafer Object
    ConstructWafer(xPosWafer, yPosWafer, zPosWafer, true);
    // **********************************
    // Construction of Overlayer on Wafer
    // **********************************
    G4Material* passMaterial = Ceramic;
    passLayer = new G4Box("PassLayer", waferlength/2, waferwidth/2, passlayerthickness/2);
    passLayerlog = new G4LogicalVolume(passLayer, passMaterial, "passLayerlog");
    if (overlayerpresence)
        { passLayerphys = new G4PVPlacement(0, passlayerpos, passLayerlog, "passLayerphys", logicalWorld, false, 0, true); }
    // *******************************************
    // Construction of Aluminum Box around package
    // *******************************************
    
        if (alboxpresence) { ConstructBox(0.8 * mm); }

    // ***********************************************************
    // Construction of Silicon 'backscattering' chunk behind wafer
    // ***********************************************************
    G4double chunkdepth = 1000 * um;
    silChunk = new G4Box("SilChunkBox", waferlength/2, waferwidth/2, chunkdepth/2);
    silChunk_log = new G4LogicalVolume(silChunk, Silicon, "SilChunk");

    G4double chunkZpos = -1*(height/2 - cavD + waferdepth/2) + waferdepth/2 + chunkdepth/2;
    silChunk_xpos = 3.0*cm;
    silChunk_ypos = 3.0*cm;
    silChunk_zpos = chunkZpos;
    // Constructing the backscatter layer
    ConstructBackscatter(silChunk_xpos, silChunk_ypos, silChunk_zpos);
    // ************
    // Data volumes
    // ************
    fbottom = logicBot; 
    flid = logicLid;
    fOverLayer = passLayerlog;

    G4cout << "We are now going though the physical volumes !!" << G4endl;
    for(G4PVPlacement* vol : PhysList)
    {
        G4bool istrue = vol->CheckOverlaps();
    }

    return physicalWorld;
}
void MyDetectorConstruction::ConstructWafer(G4double xpos, G4double ypos, G4double zpos, G4bool initialplacement)
{   
    // Deleting these members if they already exist
    if(physwafer)     { pvs->DeRegister(physwafer); delete physwafer; }
    
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
            // building the overlayer
            passlayerxpos += deltax;
            passlayerypos += deltay;
            passlayerzpos += deltaz;

            ConstructOverLayer(passlayerxpos, passlayerypos, passlayerzpos);
        }
        if(backscatterpresence)
        {
            // building the backscatter layer
            silChunk_xpos += deltax;
            silChunk_ypos += deltay;
            silChunk_zpos += deltaz;

            ConstructBackscatter(silChunk_xpos, silChunk_ypos, silChunk_zpos);
        }
    }
    // Updating the wafer position in accordance with input parameters to the construct function
    G4ThreeVector waferPosition = G4ThreeVector(xPosWafer, yPosWafer, zPosWafer);
    physwafer = new G4PVPlacement(0, waferPosition, logwafer, "physwafer", logicalWorld, false, 0, true);
    ConstructScoringLayers(numscoring, startZpos, sliceDepth);
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
    // Method that builds the scoringlayer slices within the wafer. Must be called after wafer 'shadow volume' is placed. 
    for(int i = 0; i < num_scoring; i++)
    {  
        pvs->DeRegister(PhysList[i]);
        delete PhysList[i];

        // Creating the Physical Volumes
        PhysList[i] = new G4PVPlacement(0, G4ThreeVector(0., 0., startZpos + i * sliceDepth), ScoringLog, "ScoringPhys", logwafer, false, i, true);
    }
}
void MyDetectorConstruction::ConstructBackscatter(G4double xpos, G4double ypos, G4double zpos)
{
    // Method that builds the backscattering layer behind the wafer slices.
    if(silChunk_phys){ pvs->DeRegister(silChunk_phys);
                         delete silChunk_phys; }

    G4ThreeVector position;
    position = G4ThreeVector(xpos, ypos, zpos);
    silChunk_phys = new G4PVPlacement(0, position, silChunk_log, "SilChunkPhys", logicalWorld, false, 0, true);
}
void MyDetectorConstruction::ConstructBox(G4double thickness)
{
    G4double basdim = xWorld/2;
    boxThickness = thickness;

    if(AlBox) { pvs->DeRegister(AlBox);
                delete AlBox; }
    if(AlBox_log) { lvs->Dedelete AlBox_log; }
    if(AlBox_phys) { delete AlBox_phys; }

    if (pbBoxpresence) { ConstructLead((basdim + thickness), 2*mm); }

    G4Box *AirChunk = new G4Box("AirChunk", basdim, basdim, basdim);
    G4Box *AlChunk = new G4Box("AlChunk", basdim + thickness, basdim + thickness, basdim + thickness);
    AlBox = new G4SubtractionSolid("Box", AlChunk, AirChunk, 0, G4ThreeVector(0., 0., 0));

    AlBox_log = new G4LogicalVolume(AlBox, Aluminum, "LogBox");
    AlBox_phys = new G4PVPlacement(0, G4ThreeVector(0., 0., 3.75 * cm), AlBox_log, "physBox", logicalWorld, false, 0, true);
}
void MyDetectorConstruction::ConstructLead(G4double cavsize, G4double thickness)
{
    pbCavSize = cavsize;
    pbThickness = thickness;

    G4double basdim = cavsize;
    if (LeadBox) { delete LeadBox; }
    if (LeadBox_log) { delete LeadBox_log; }
    if (LeadBox_phys) { delete LeadBox_phys; }

    G4Box *LeadAir = new G4Box("PbAirChunk", basdim, basdim, basdim);
    G4Box *LeadChunk = new G4Box("PbChunk", basdim + thickness, basdim + thickness, basdim + thickness);
    LeadBox = new G4SubtractionSolid("PbBox", LeadChunk, LeadAir, 0, G4ThreeVector(0., 0., 0.));

    LeadBox_log = new G4LogicalVolume(LeadBox, lead, "LogPb");
    if(pbBoxpresence) { LeadBox_phys = new G4PVPlacement(0, G4ThreeVector(0., 0., 3.75*cm), LeadBox_log, "physPb", logicalWorld, false, 0, true); }
}
void MyDetectorConstruction::LeadBoxChanger(G4bool presence)
{
    pbBoxpresence = presence;
    ConstructLead(pbCavSize, pbThickness);
}
