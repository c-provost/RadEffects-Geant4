#ifndef construction_hh
#define construction_hh


#include "G4VUserDetectorConstruction.hh"
#include "G4SubtractionSolid.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4SystemOfUnits.hh"
#include "RadPackSensitiveDetector.hh"

#include "G4Material.hh"


class RadiationDetectorConstruction : public G4VUserDetectorConstruction
{
    public:
   // Constructor/Destructor
    RadiationDetectorConstruction();
    ~RadiationDetectorConstruction();

   // Method that constructs the volumes in the simulation
    virtual G4VPhysicalVolume* Construct();
    void DefineMaterials();
    void ConstructLid();
    void ConstructBot();
    void ConstructPlane(G4double, G4double, G4double, G4ThreeVector);  // Constructing the Pb-Al Plane per MIL STD 883
    virtual void ConstructSDAndField();
    void ConstructWafer(G4double, G4double, G4double, G4ThreeVector);
    void ConstructScoringLayers(G4double, G4double, G4double, G4double);

    private:
   // The values that store key information about the simulation. 
   // The x, y, and z dimensions of the world volume
    G4double xDimWorld, yDimWorld, zDimWorld;

   // The x, y, and z positions of the center of the mass of scoring volumes. 
    G4double xposScoring, yposScoring, zposScoring;

   // Solid, Logical, and Physical Volumes for the World Volume
    G4Box*
    theWorld,
    *mainBody, *cavity;

    G4SubtractionSolid*
    Bot, *Lid;

    G4LogicalVolume* logicBot, *logicLid;
    G4VPhysicalVolume* physBot,
                        *physLid;

    G4LogicalVolume* theWorldLog;
    G4VPhysicalVolume* theWorldPhys;
   // The logical volume that corresponds to a single slice. 
    G4LogicalVolume* sliceLog;
    G4Material 
    *theWorldMaterial, *Aluminum, *Gold, *Tungsten, *Steel, *Lead,
    *Silicon, *Ceramic, *SiO2, *plastic;
   // These are the volume store objects that are used for changing the volumes in the simulation. 
   // In order to do so, volumes need to be deregistered in their respective stores

    G4PhysicalVolumeStore* pvs;
    G4LogicalVolumeStore* lvs;
   // The structure that stores the package dimension information
    struct pdim;

    RadPackSensitiveDetector *theDetector;

};


#endif