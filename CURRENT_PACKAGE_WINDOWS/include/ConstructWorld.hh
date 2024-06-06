#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"
#include "G4GeometryManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4RunManager.hh"
#include "G4PVReplica.hh"
#include "G4Region.hh"
#include "G4UserLimits.hh"
#include "G4Tubs.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4SubtractionSolid.hh"

#include "DetectorMessenger.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    // The method that builds the wafer
    void ConstructWafer(G4double, G4double, G4double, G4bool);
    // The method that builds the scoring layers within the wafer
    void ConstructScoringLayers(G4double, G4double, G4double);
    // The method that builds the overlayer
    void ConstructOverLayer(G4double xpos, G4double ypos, G4double zpos);
    // The mathod that builds the backscattering Layer
    void ConstructBackscatter(G4double xpos, G4double ypos, G4double zpos);
    // The method that build the aluminum box
    void ConstructBox(G4double thickness);

    // Volume returners for Lid and Bottom
    G4LogicalVolume* GetVolumeLid()   const { return flid;   }
    G4LogicalVolume* GetVolumeBot()   const { return fbottom;}

    // Overlayer Returner
    G4LogicalVolume* GetVolumeOverlayer() const { return fOverLayer; }

    // Scoring Volume Returner for Data Collection
    //↓ What is this type?
    auto GetScoringVolumes(G4int scoringvolume) const { return LogList[scoringvolume - 1]; }


private:
    // *****************
    // The variable Farm
    // *****************
    G4double xPosWafer, yPosWafer, zPosWafer;

    // Constants
    G4double cavD; G4double cavL; G4double cavW;

    // Dimensions as Listed in MIL-STD 883 1019
    G4double D, E, A, Q, height;

    G4double waferdepth, waferlength, waferwidth;

    // Package Chunk information
    G4double packChunkwidth, packChunklength;

    // Bottom and lid information
    G4ThreeVector bottompos, lidpos;

    // Overlayer information
    G4double passlayerthickness;
    G4double passlayerxpos, passlayerypos, passlayerzpos;
    G4ThreeVector passlayerpos;
    G4double sliceDepth, numslices, startZpos;

    // Material  Contruction routine
    void DefineMaterials();
    G4Material *worldMaterial, *Steel, *Gold, *polyStyrene,
               *Aluminum, *Tungsten, *Silicon, *Ceramic,
               *SiO2, *plastic, *poly;

    // World Volume
    G4double xWorld, yWorld, zWorld;
    G4Box *solidWorld;
    G4LogicalVolume *logicalWorld;
    G4VPhysicalVolume *physicalWorld;

    // Package Volumes
    G4Box *mainBody, *cavity;
    G4SubtractionSolid *Lid, *Bot;
    G4LogicalVolume *logicLid, *logicBot;
    G4PVPlacement *physLid, *physBot;

    // Computer Chip Volumes
    G4Box *wafer, *Slice_Stub;
    G4LogicalVolume *logwafer, *LogList[60] = {};
    G4PVPlacement *physwafer, *PhysList[60] = {};

    // Overlayers of Wafer
    G4Box* passLayer;
    G4LogicalVolume* passLayerlog;
    G4PVPlacement*   passLayerphys;
    
    // Sensitive Volumes (which we collect information about the simulation from)
    G4LogicalVolume *fbottom, *flid, 
                    *fOverLayer,
                    *fwafer, *fLogList[60] = {};



    //int numels = 10;
    //std::vector<G4double> fLogList2 = {};
    //fLogList2.resize(numels);

    // Aluminum Box Volume
    G4SubtractionSolid *AlBox;
    G4LogicalVolume *AlBox_log;       
    G4PVPlacement *AlBox_phys;

    // Silicon Chunk behind the scoring layers
    G4Box* silChunk;
    G4LogicalVolume* silChunk_log;
    G4PVPlacement * silChunk_phys;
    G4double silChunk_xpos, silChunk_ypos, silChunk_zpos;

    // Boolean values
    G4bool lidpresence, bottompresence, overlayerpresence, alboxpresence, backscatterpresence;

};

#endif