#include "RadPackGeometryMessenger.hh"




RadPackDetectorMessenger::RadPackDetectorMessenger(RadiationDetectorConstruction* inheritedDetector)
{
    // Setting this object's associated geometry to that which is instantiated with it.
    detector = inheritedDetector;

   // Initializing the geometry has changed flag to false. Get's updated when command line commands are given
    GeometryHasChanged = false;

   // Initializing a directory where simulation geometry commands will reside
    fDetectorDir = new G4UIdirectory("/SimGeometry/");
        fDetectorDir->SetGuidance("Simulation Geometry Commands");
   // Creating a positional subdirectory that the plane position commands will sit in. 
    fPositionalDir = new G4UIdirectory("/SimGeometry/Positional");
        fPositionalDir->SetGuidance("Pb-Al Plane Construction Position");
   // making the pb-al plane. Will send the command through a pointer to the detectorgeometry
    makePlane = new G4UIcmdWithADoubleAndUnit("/SimGeometry/Positional/makePlane", this);
        makePlane->SetGuidance("The command that draws the plane in elsewhere in the simulation");
        makePlane -> AvailableForStates(G4State_PreInit, G4State_Idle);
        makePlane -> SetParameterName("z-position", false);

   // Making the command that lets the run manager know of the geometry update
    applyChangesToGeometryCmd = new G4UIcmdWithoutParameter("/SimGeometry/applyChanges", this);
        applyChangesToGeometryCmd->SetGuidance("Updates Geometry Within the Run manager");
        applyChangesToGeometryCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

}

RadPackDetectorMessenger::~RadPackDetectorMessenger(){}

void RadPackDetectorMessenger::SetNewValue(G4UIcommand* command, G4String commandContent)
{
    
   // Checking what the command is: I wonder if this can be done more beautifully. Perhaps switch case?
    if (command == makePlane)
    {
        G4double zPosPlane = G4UIcmdWithADoubleAndUnit::GetNewDoubleValue(commandContent);

        G4cout << "<Plane Geometry Command>" <<
            G4endl << " <zposition>: " << zPosPlane/cm << " cm" << G4endl;

        detector->ConstructPlane(zPosPlane);
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

        else{ G4cout << "Geometry is up to date! - Ignoring applyChanges command" << G4endl; 
    }
    }
}