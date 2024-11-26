#include "RadPackConstruction.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4Tubs.hh"


#include "G4UnionSolid.hh"
#include "dimensions.hh"

RadiationDetectorConstruction::RadiationDetectorConstruction()
{
   // Declaring the volume store objects. Will be accessed in the entirety of this class
   
    lvs = G4LogicalVolumeStore::GetInstance();
    pvs = G4PhysicalVolumeStore::GetInstance();
   
   // Initializing the first plane boolean flag
    firstPlaneConst = true;

   // The default depth of the Lead Wall
    planeDefaultDepth = 1.5 * mm;

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



    G4Tubs* mainDisk = new G4Tubs("theTube", 0.0 *cm, 2.75/2*cm, 0.7/2*cm, 0, 360*degree);
    G4Tubs* shaft = new G4Tubs("theShaft", 0.0*cm, .45*cm, 0.65/2*cm, 0, 360*degree);
    G4Tubs* magnet = new G4Tubs("magnet", 0.0*cm, 0.3*cm, 0.3*cm, 0, 360*degree);

    G4double rval = .85 * cm;

    G4double zPos = .35 * cm + .3*cm - 2*mm;
    G4UnionSolid* theApparatus = new G4UnionSolid("apparatus", mainDisk, shaft, 0, G4ThreeVector(0, 0, 0.675*cm));


    for(int i = 0; i<6; i++)
    {   
        G4double theta = 60 * i * 3.14159265 / 180;
        
        G4double xpos = rval * cos(theta);
        G4double ypos = rval * sin(theta);

        theApparatus = new G4UnionSolid("apparatus", theApparatus, magnet, 0, G4ThreeVector(xpos, ypos, -1*zPos));
    }
    //G4UnionSolid* appPlusMag = new G4UnionSolid("appPlusMag", theApparatus, magnet, 0, G4ThreeVector(0., ))

    G4LogicalVolume* diskVol = new G4LogicalVolume(theApparatus, Aluminum, "theApparatus");
    G4PVPlacement* diskVol_phys = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), diskVol, "theApparatus", theWorldLog, false, 0, true);


    return theWorldPhys;
}
