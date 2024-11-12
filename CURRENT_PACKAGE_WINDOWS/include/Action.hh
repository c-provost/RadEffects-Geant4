#ifndef ACTION_HH
#define ACTION_HH




#include "ParticleGun.hh"
#include "run.hh"
#include "event.hh"
#include "StepAction.hh"

class ActionInitialization : public G4VUserActionInitialization
{
public:
    ActionInitialization();
    ~ActionInitialization();

    virtual void Build() const;
    virtual void BuildforMaster() const;
};
#endif