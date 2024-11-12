#include "RunActionMessenger.hh"


PackageRunActionMessenger::PackageRunActionMessenger(RunAction* inRunAction)
{  
    // The RunAction object to which this messenger has access.
        theRunaction = inRunAction;
    // The UI directory containing commands pertinent to the whole sim
        telcmds = new G4UIdirectory("/tel_gdml/");
    // Creating the comman that sets an output filename
        setfilecmd = new G4UIcmdWithAString("/tel_gdml/hitsfile", this);
        setfilecmd->SetGuidance("output file for hits collection");
        setfilecmd->SetGuidance("default: Hits.root");
        setfilecmd->SetParameterName("savehitsfile", false);
        setfilecmd->SetDefaultValue("Hits.root");
}

PackageRunActionMessenger::~PackageRunActionMessenger()
{
    delete setfilecmd;
}

void PackageRunActionMessenger::SetNewValue(G4UIcommand *theCommand, G4String thecontent)
{
    if (theCommand == setfilecmd)
    {
        // Sending update command the RunAction Class. 
            theRunaction->SetSaveFileName(thecontent);
    }
}
