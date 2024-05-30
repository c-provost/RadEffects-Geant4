#ifndef DETMES_HH
#define DETMES_HH

#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "ConstructWorld.hh"
#include "G4RunManager.hh"

#include "ConstructWorld.hh"

class MyDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithoutParameter;



class PackageDetectorMessenger : public G4UImessenger
{
public:
    PackageDetectorMessenger(MyDetectorConstruction *inheriteddetector);
    ~PackageDetectorMessenger() override;

    void SetNewValue(G4UIcommand*, G4String) override;

private:

    MyDetectorConstruction* detector;
    // These will get defined in DetectorMessenger.cc

    bool GeometryHasChanged;
    G4UIdirectory*          fDetectorDir = nullptr;
    G4UIdirectory*          fPositionalDir = nullptr;

    G4UIcmdWithoutParameter *applyChangesToGeometryCmd = nullptr;

    G4UIcmdWithADoubleAndUnit *updateWaferYpos = nullptr;
    G4UIcmdWithADoubleAndUnit *updateWaferXpos = nullptr;
    G4UIcmdWithADoubleAndUnit *updateWaferZpos = nullptr;
    
    G4double yPosWafer, xPosWafer, zPosWafer;

public:
    G4double GetyPosWafer();

};


#endif