#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"

#include "G4AnalysisManager.hh"
#include "G4Accumulable.hh"
#include "globals.hh"

#include "Dose.hh"
class RunAction : public G4UserRunAction
{
public:
    RunAction();  // Constructor
    ~RunAction(); //  Destructor 

    // Routines for the beginning and end of the run. Native to G4. 
    virtual void BeginOfRunAction(const G4Run*) override;
    virtual void EndOfRunAction(const G4Run*) override;

    void AddDose(G4int index, G4double dose);
    void primaryinoverlayercounter();
    DoseInformation* GetDoseInfo();

    G4int primarycounter = 0;
    G4int numscoringlayers;

private:
    // In this array (Dose_values[22]), the indicies correspond to the layer in which dose is deposited.
    // Index 0 & 61 correspond to the dose in the lid and bottom of  the package, respectively.
    G4double Dose_values[62];
    G4double allthedoses;
    G4double dummyarray[62] = {};
    std::vector<G4double> myvalues;
    DoseInformation* doseinfo;

};

#endif