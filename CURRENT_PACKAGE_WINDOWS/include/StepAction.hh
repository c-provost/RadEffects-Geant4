#ifndef STEPACTION_HH
#define STEPACTION_HH


#include "G4UserSteppingAction.hh"
#include "G4Step.hh"

#include "event.hh"
#include "ConstructWorld.hh"

class SteppingAction : public G4UserSteppingAction
{
public:
    SteppingAction(EventAction* eventAction);
    ~SteppingAction();

    virtual void UserSteppingAction(const G4Step*);

private:
    EventAction* fEventAction;
};
#endif