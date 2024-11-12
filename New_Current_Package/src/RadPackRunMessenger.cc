#include "RadPackRunMessenger.hh"


RadPackRunMessenger::RadPackRunMessenger(RadPackRunAction* inRunAction)
{  
    // The RunAction object to which this messenger has access.
        theRunaction = inRunAction;
    // The UI directory containing commands pertinent to the whole sim
        radcmds = new G4UIdirectory("/RadiationPack/");
    // Creating the comman that sets an output filename
        setfilecmd = new G4UIcmdWithAString("/RadiationPack/hitsfile", this);
        setfilecmd->SetGuidance("output file for hits collection");
        setfilecmd->SetGuidance("default: Hits.root");
        setfilecmd->SetParameterName("savehitsfile", false);
        setfilecmd->SetDefaultValue("Hits.root");
}

RadPackRunMessenger::~RadPackRunMessenger()
{
    delete setfilecmd;
}

void RadPackRunMessenger::SetNewValue(G4UIcommand *theCommand, G4String thecontent)
{
    if (theCommand == setfilecmd)
    {
        // Sending update command the RunAction Class. 
            theRunaction->SetSaveFileName(thecontent);
    }
}
