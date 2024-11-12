#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"
#include "G4Accumulable.hh"
#include "globals.hh"


class RadPackRunAction : public G4UserRunAction
{
public:
    RadPackRunAction();  // Constructor
    ~RadPackRunAction(); //  Destructor 

    // Routines for the beginning and end of the run. Native to G4. 
    virtual void BeginOfRunAction(const G4Run*) override;
    virtual void EndOfRunAction(const G4Run*) override;

   // The method that sets the name of the output data file.
    void SetSaveFileName(G4String saveFileName);

    // The count of total primaries that enter the overlayer in a given run. Reset at the end of each run
    G4int primarycounter = 0;
    // The number of scoring layers who collect data
    G4int numscoringlayers;

private:
    
    // The string that the run class uses to set as an output file. 
    G4String SaveFileName;
};

#endif