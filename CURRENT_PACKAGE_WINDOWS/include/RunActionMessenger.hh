#ifndef RAM_HH
#define RAM_HH

#include "G4UImessenger.hh"
#include "run.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"

class PackageRunActionMessenger : public G4UImessenger
{
    // Class to allow for user access to RunAction class from 
    // UI Terminal. Includes a method to update the name of
    // the output file that the RunAction class opens at the
    // beginning of a run.
    public:
        PackageRunActionMessenger(RunAction* inRunAction);
        ~PackageRunActionMessenger();

        // Inherited method from G4UImessenger object. Required for 
        // updating values in other classes.
        void SetNewValue(G4UIcommand*, G4String);

    private:
        // The RunAction Class (user-defined)
            RunAction* theRunaction;
        // UI Pointers defined in .cc file
            G4UIcmdWithAString* setfilecmd;
            G4UIdirectory *telcmds;

};

#endif