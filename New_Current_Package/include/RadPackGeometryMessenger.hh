#ifndef GEOM_MESS
#define GEOM_MESS

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcommand.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"


#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "RadPackConstruction.hh"

#include "G4RunManager.hh"
#include "RadPackConstruction.hh"

class RadiationDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithoutParameter;

class RadPackDetectorMessenger : public G4UImessenger
{
public:
    RadPackDetectorMessenger(RadiationDetectorConstruction*);
    ~RadPackDetectorMessenger() override;

    void SetNewValue(G4UIcommand*, G4String) override;

private:

    RadiationDetectorConstruction* detector;
    // These will get defined in DetectorMessenger.cc

    bool GeometryHasChanged;
    G4UIdirectory*          fDetectorDir = nullptr;
    G4UIdirectory*          fPositionalDir = nullptr;

    G4UIcmdWithoutParameter *applyChangesToGeometryCmd = nullptr;
    G4UIcmdWithADoubleAndUnit *makePlane = nullptr;

    // G4UIcmdWithADoubleAndUnit *updateWaferXpos = nullptr;
    // G4UIcmdWithADoubleAndUnit *updateWaferZpos = nullptr;
    
    // G4double yPosWafer, xPosWafer, zPosWafer;


};


#endif