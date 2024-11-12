#ifndef RAM_HH
#define RAM_HH

#include "G4UImessenger.hh"
#include "RadPackRunAction.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"

class RadPackRunMessenger : public G4UImessenger
{
    // Class to allow for user access to RunAction class from 
    // UI Terminal. Includes a method to update the name of
    // the output file that the RunAction class opens at the
    // beginning of a run.
    public:
        RadPackRunMessenger(RadPackRunAction* inRunAction);
        ~RadPackRunMessenger();

        // Inherited method from G4UImessenger object. Required for 
        // updating values in other classes.
        void SetNewValue(G4UIcommand*, G4String);

    private:
        // The RunAction Class (user-defined)
            RadPackRunAction* theRunaction;
        // UI Pointers defined in .cc file
            G4UIcmdWithAString* setfilecmd;
            G4UIdirectory *radcmds;

};

#endif