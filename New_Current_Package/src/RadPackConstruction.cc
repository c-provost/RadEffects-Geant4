#include "RadPackConstruction.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"



#include "dimensions.hh"

RadiationDetectorConstruction::RadiationDetectorConstruction()
{
   // Declaring the volume store objects. Will be accessed in the entirety of this class
   
    lvs = G4LogicalVolumeStore::GetInstance();
    pvs = G4PhysicalVolumeStore::GetInstance();
   


   // Initializing the dimensions of the world volume
    xDimWorld = 10*cm;
    yDimWorld = 10*cm;
    zDimWorld = 0.61 * m;

    DefineMaterials();

}

void RadiationDetectorConstruction::DefineMaterials()
{
    G4NistManager* nist = G4NistManager::Instance();

    // Defining the materials in the simulation
    theWorldMaterial = nist->FindOrBuildMaterial("G4_AIR");
    Aluminum      = nist->FindOrBuildMaterial("G4_Al");
    Gold          = nist->FindOrBuildMaterial("G4_Au");
    Tungsten      = nist->FindOrBuildMaterial("G4_W");
    Steel         = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
    Silicon       = nist->FindOrBuildMaterial("G4_Si");
    Ceramic       = nist->FindOrBuildMaterial("G4_ALUMINUM_OXIDE");
    SiO2          = nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
    plastic       = nist->FindOrBuildMaterial("G4_POLYVINYL_CHLORIDE");
    Lead          = nist->FindOrBuildMaterial("G4_Pb");
}

RadiationDetectorConstruction::~RadiationDetectorConstruction()
{}

G4VPhysicalVolume* RadiationDetectorConstruction::Construct()
{
   // Building the world volume, which must be returned by this function
    theWorld = new G4Box("theWorld", xDimWorld, yDimWorld, zDimWorld);                                            // The geometric outline of the world volume 
    theWorldLog = new G4LogicalVolume(theWorld, theWorldMaterial, "theWorld");                                    // The the aspect of the volume that controls information
    theWorldPhys = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), theWorldLog, "theWorld", 0, false, 0, false);   // The physical placement of the volume
        // Note: these volumes all are given the name, "theWorld"  for reverence in the volume stores if necessary. 
    
    // This should be made into a routine that takes in the physical volume and spits this information out by itself -CP 09/24/24 1:41pm
    G4cout << "World Construction!\n    <Shape>: G4Box" << G4endl <<
        "       <xDimension>: " << xDimWorld/cm << "cm" << G4endl << 
        "       <yDimension>: " << yDimWorld/cm << "cm" << G4endl <<
        "       <zDimension>: " << zDimWorld/cm << "cm" << G4endl << G4endl;

    mainBody = new G4Box("packChunk", PackageDimensions::packChunkwidth/2,
                                                PackageDimensions::packChunklength/2,
                                                PackageDimensions::height/2);
    cavity = new G4Box("Cav1", PackageDimensions::cavL/2, PackageDimensions::cavW/2, PackageDimensions::cavD/2);

    G4cout << "cavW: " << PackageDimensions::cavW/cm << G4endl;
    G4cout << "cavL: " << PackageDimensions::cavL/cm << G4endl;
    G4cout << "cavD: " << PackageDimensions::cavD/cm << G4endl;

/*
   // Constructing the scoring layers
    G4int numslices = 20; 
    G4double sliceDepth = PackageDimesnsions::waferdepth/numslices;
    G4Material* SliceMaterial = Silicon;
    
    Slice_Stub = new G4Box("Slice_Stub", PackageDimensions::waferlength/2, PackageDimensions::waferwidth/2, sliceDepth/2);
    Slice_log = new G4LogicalVolume(Slice_Stub, SliceMaterial, "logSlice");
    startZpos = -1 * (pdim::waferdepth/2) + pdim::sliceDepth/2;
*/
   // Storing this here for now, needs to get relocated. 
   // Logical volume that stores the hit information. 
 //   sliceLog = new G4LogicalVolume(Slice_Stub, SliceMaterial, "sliceLog");

    //ConstructBot();
    //ConstructLid();



    ConstructWafer(.5*cm, .7*cm, 500*um, G4ThreeVector(0., 0., 0.5*m));
    ConstructScoringLayers(20, .5*cm, .7*cm, 500*um);
    ConstructPlane(xDimWorld*2, yDimWorld*2, 1.5*mm, G4ThreeVector(0, 0, -0.2*m));



    ConstructSDAndField();
    return theWorldPhys;
}

void RadiationDetectorConstruction::ConstructBot()
{
    Bot = new G4SubtractionSolid("Bot", mainBody, cavity, 0, G4ThreeVector(3.0 *cm, 3.0*cm, -1*(PackageDimensions::height-PackageDimensions::cavD)/2));
    logicBot = new G4LogicalVolume(Bot, Ceramic, "logicBot");
    physBot = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicBot, "physBot", theWorldLog, false, 0, true);
}

void RadiationDetectorConstruction::ConstructSDAndField()
{

    G4cout << "I am constructing here: " << G4endl;
    theDetector = new RadPackSensitiveDetector("DoseDetector");
    G4LogicalVolume *theScoring = lvs->GetVolume("sliceLog");
    theScoring->SetSensitiveDetector(theDetector);


}

void RadiationDetectorConstruction::ConstructLid()
{
    Lid = new G4SubtractionSolid("Lid", mainBody, cavity, 0, G4ThreeVector(0., 0., (PackageDimensions::height-PackageDimensions::cavD)/2));
    logicLid = new G4LogicalVolume(Lid, Ceramic, "logicLid");
    physLid = new G4PVPlacement(0, G4ThreeVector(0., 0., -1*(PackageDimensions::height + PackageDimensions::cavD + 650 * um)), logicLid, "physLid", theWorldLog, false, 0, true);
}


void RadiationDetectorConstruction::ConstructScoringLayers(G4double numslices, G4double waferLength, G4double waferWidth, G4double waferDepth)
{
    G4LogicalVolume* theWaferLog = lvs->GetVolume("theWafer");
    G4String volumeTitle = "slicePhys";
    G4cout << "! Scoring Layer Construction! " << G4endl
        << "\tNumSlices: " << numslices << G4endl;

   // Obtaining the dimensions of the wafer box, to fill with scoring volumes
        G4double sliceLength = waferLength;
        G4double sliceWidth = waferWidth;
        G4double sliceDepth = waferDepth/numslices;
            G4cout << "sliceDepth: " << sliceDepth/cm << G4endl;
        G4Box *theSliceSolid = new G4Box("sliceBox", sliceLength/2, sliceWidth/2, sliceDepth/2);
        
        G4LogicalVolume* theSliceLog = new G4LogicalVolume(theSliceSolid, Silicon, "sliceLog");
        
        G4cout << "<ScoringLayerDepth>: " << sliceDepth << G4endl;
        G4double startZpos = -1*waferDepth/2 + sliceDepth/2;
        G4cout << "Start z pos" << startZpos/cm << G4endl;

    for (int i = 0; i < numslices; i++)
    {
       // Using the index to remove the pv with the corresponding copy no. 
        G4String volumeTitle = "slicePhys";

        G4VPhysicalVolume* newSliceVol = new G4PVPlacement(0, G4ThreeVector(0., 0., startZpos + i*sliceDepth), theSliceLog, volumeTitle, theWaferLog, false, i, true);
    }
    

}

void RadiationDetectorConstruction::ConstructPlane(G4double length, G4double width, G4double depth, G4ThreeVector position)
{
    // This is the methhod that will construct the Pb-Al plane in front of our test article. This will be the same x and y dimensions as the world volume.

    G4VSolid *pB_plane; G4LogicalVolume *pB_plane_log; G4VPhysicalVolume* pB_plane_phys;
    G4VSolid *al_plane; G4LogicalVolume *al_plane_log; G4VPhysicalVolume* al_plane_phys;

    //pvs->DeRegister(pvs->GetVolume("PbPlane"));
    //lvs->DeRegister(lvs->GetVolume("PbPlane"));

   // Instituting the input parameters as full lengths because that feels more ergonomic. Translating to half-lengths for G4
    pB_plane = new G4Box("PbPlane", length/2, width/2, depth/2);
    pB_plane_log = new G4LogicalVolume(pB_plane, Lead, "PbPlane");
    pB_plane_phys = new G4PVPlacement(0, position, pB_plane_log, "PbPlane", theWorldLog, false, 0, true);

   // Generating an aluminum plane that immediately follows the lead one. 
    al_plane = new G4Box("AlPlane", length/2, width/2, 400*um);
    al_plane_log = new G4LogicalVolume(al_plane, Aluminum, "AlPlane");

  // Creating the center of the al layer, immediately succeeding the PbPlane.
  // 400 um  added because that is the depth of the aluminum plane.
    G4ThreeVector alPosition = position + G4ThreeVector(0, 0, -1 * depth/2 - 400*um);
    al_plane_phys = new G4PVPlacement(0, alPosition, al_plane_log, "AlPlane", theWorldLog, false, 0, true);
}



void RadiationDetectorConstruction::ConstructWafer(G4double length, G4double width, G4double height, G4ThreeVector position)
{
    G4cout << "<WaferConstruction!>" << G4endl << "\t" << "<xDim>: " << length << G4endl
            << "\t" << "yDim>: " << width << G4endl
            << "\t" << "<zDim>: " << height << G4endl
            << "\t" << "<position>: " << position << G4endl;

   // The name that will be assigned to the logical, physical, and solid volumes 
    G4String thisVolumeName = "theWafer";

   // Constructing the Solid, Logical Volume, and Physical Volume for the wafer.
    G4Box* waferSolid = new G4Box(thisVolumeName, length/2, width/2, height/2);
    G4LogicalVolume* waferLogic = new G4LogicalVolume(waferSolid, Silicon, thisVolumeName);
    G4VPhysicalVolume* waferPhys = new G4PVPlacement(0, position, waferLogic, thisVolumeName, theWorldLog, false, 0, true);
}

