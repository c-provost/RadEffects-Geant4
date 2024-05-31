#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"

#include "event.hh"
#include "run.hh"
#include "Dose.hh"

class EventAction : public G4UserEventAction
{
public:
    EventAction(RunAction* runAction);
    ~EventAction();
    
    // Native to G4 Event Routines
    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);

    // *******************
    // Energy Dep Routines 
    // *******************

    // Energy Dep adder for the lid and bottom
    void addEnergydepLid  (G4double edepLid  ) {   fEdep_lid += edepLid;   }
    void addEnergydepBot  (G4double edepBot  ) {   fEdep_bot += edepBot;   }

    // Event-Scale Energy Dep adder for wafer layers. 
    void addEnergydep (G4int ScoringLayer, G4double edep) { G4int index = ScoringLayer-1; fEdepScoring[index] += edep; }

    // Primary Counter
    void primaryinoverlayercounter();


    //
    // * Dose-adding function to be sent to runAction *
    //
    void AddDose(G4int scoringvolume, G4double edep) {  fRunAction->AddDose(scoringvolume ,edep); }


private:
    G4double fEdep_lid, fEdep_bot;
    G4double fEdepScoring[60] = {};

    G4int i_counters[62] = {};
    G4double dose_tot_list[62] = {};
    G4double dose_avg_list[62] = {};
    G4double edep_tot_list[62] = {};
    G4double edep_avg_list[62] = {};
    
protected: 
   RunAction* fRunAction;
};

#endif