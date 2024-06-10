
#include "DetectorMessenger.hh"
#include "ConstructWorld.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcommand.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "ConstructWorld.hh"

PackageDetectorMessenger::PackageDetectorMessenger(MyDetectorConstruction *inheriteddetector)
{   
    // The Detector That this messenger controlls
    detector = inheriteddetector;

    // Self-explanatory flag that gets updated with UI Commands 
    GeometryHasChanged = false;
    // UI Directory that corresponds to adjusting hte detector geometry 
    fDetectorDir = new G4UIdirectory("/DetectorGeometry/");
      fDetectorDir -> SetGuidance("Detector Geometry commands");
    // Positional Directory
    fPositionalDir = new G4UIdirectory("/DetectorGeometry/Positional/");
      fPositionalDir -> SetGuidance("The Positional Commands for the Detector Geometry");
    // Methods to update the  position of the wafer
    updateWaferYpos = new G4UIcmdWithADoubleAndUnit("/DetectorGeometry/Positional/yPosWafer", this);
      updateWaferYpos -> SetGuidance("Update the Y-position of the wafer");
      updateWaferYpos -> AvailableForStates(G4State_PreInit, G4State_Idle);
      updateWaferYpos -> SetParameterName("y-value", false);

    updateWaferXpos = new G4UIcmdWithADoubleAndUnit("/DetectorGeometry/Positional/xPosWafer", this);
      updateWaferXpos -> SetGuidance("Update the X-position of the wafer");
      updateWaferXpos -> AvailableForStates(G4State_PreInit, G4State_Idle);
      updateWaferXpos -> SetParameterName("x-value", false);

    updateWaferZpos = new G4UIcmdWithADoubleAndUnit("/DetectorGeometry/Positional/zPosWafer", this);
      updateWaferZpos -> SetGuidance("Update the Z-position of the wafer");
      updateWaferZpos -> AvailableForStates(G4State_PreInit, G4State_Idle);
      updateWaferZpos -> SetParameterName("z-value", false);

    // Command to send the 'Geometry Has Changed' Flag to the run manager 
    applyChangesToGeometryCmd = new G4UIcmdWithoutParameter("/DetectorGeometry/applyChanges", this);
      applyChangesToGeometryCmd -> SetGuidance("Apply selected changes to the geometry");
      applyChangesToGeometryCmd -> AvailableForStates(G4State_PreInit, G4State_Idle);
    
    // AlBox Directory
    fBoxDir = new G4UIdirectory("/BoxGeometry/");
      fBoxDir -> SetGuidance("Al Box Directory");

    // Command to update the thickness of the AlBox
    updateBoxThickness = new G4UIcmdWithADoubleAndUnit("/BoxGeometry/updateThickness", this);
      updateBoxThickness -> SetGuidance("Update the thickness of the Al box");
      updateBoxThickness -> AvailableForStates(G4State_PreInit, G4State_Idle);
      updateBoxThickness -> SetParameterName("thickness", false);

    // Command to change whether the Pb box is present
    pbBoxpresence = new G4UIcmdWithABool("/BoxGeometry/pbPresence", this);
      pbBoxpresence -> SetGuidance("Update the presence of the Pb Box");
      pbBoxpresence -> AvailableForStates(G4State_PreInit, G4State_Idle);
      pbBoxpresence -> SetParameterName("status", false);
      

}   
PackageDetectorMessenger::~PackageDetectorMessenger()
{
  delete updateBoxThickness;

  delete updateWaferZpos;
  delete updateWaferXpos;
  delete updateWaferYpos;

  delete applyChangesToGeometryCmd;

  delete fBoxDir;
  delete fDetectorDir;
  delete fPositionalDir;
}

void PackageDetectorMessenger::SetNewValue(G4UIcommand* command, G4String commandContent)
{
    // ********* Positional Command Farm ********** // 
    if (command == updateWaferYpos)
    {
        G4double yPosWafer = G4UIcmdWithADoubleAndUnit::GetNewDoubleValue(commandContent);
        G4cout << "The new y pos is " << yPosWafer/cm << G4endl;
        detector->ConstructWafer(1010101, yPosWafer, 1010101, false);
        GeometryHasChanged = true;
    }
    if (command == updateWaferXpos)
    {
        G4double xPosWafer = G4UIcmdWithADoubleAndUnit::GetNewDoubleValue(commandContent);
        G4cout << "The new x pos is " << xPosWafer/cm << "cm" << G4endl;
        detector->ConstructWafer(xPosWafer, 1010101, 1010101, false);
        GeometryHasChanged = true;
    }
    if (command == updateWaferZpos)
    {
        G4double zPosWafer = G4UIcmdWithADoubleAndUnit::GetNewDoubleValue(commandContent);
        G4cout << "The new z pos is " << zPosWafer/cm << "cm" << G4endl;
        detector->ConstructWafer(1010101, 1010101, zPosWafer, false);
        GeometryHasChanged = true;
    }
    if (command == updateBoxThickness)
    {
      G4double newthickness = G4UIcmdWithADoubleAndUnit::GetNewDoubleValue(commandContent);
      G4cout << "The requested box thickness is " << newthickness/um << "um" << G4endl;
      detector->ConstructBox(newthickness);
      GeometryHasChanged = true;
    }
    if (command == pbBoxpresence)
    {
      G4bool value = G4UIcmdWithABool::GetNewBoolValue(commandContent);
      G4cout << "Pb Box Presence changed!" << G4endl;
      detector -> LeadBoxChanger(value);
      GeometryHasChanged = true;
    }
    if (command == applyChangesToGeometryCmd)
    {
        if(GeometryHasChanged == true)          {
        G4RunManager *runManager = G4RunManager::GetRunManager();
        G4cout << "The Geometry Has Been Modified " << G4endl;

        GeometryHasChanged = false;

        // Lets the RunManager know about changes to the geometry. 
        runManager->GeometryHasBeenModified();  }

        else{ G4cout << "Geometry is up to date! - Ignoring applyChanges command" << G4endl; }
    }

}
