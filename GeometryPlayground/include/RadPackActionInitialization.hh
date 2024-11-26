#ifndef action_hh
#define action_hh

#include "G4VUserActionInitialization.hh"

// Object that takes in user action classes and connects them with the run manager.
class RadPackActionInitialization : public G4VUserActionInitialization
{
    public:
    RadPackActionInitialization();
    ~RadPackActionInitialization();


    // Inherited methods from Geant4 source code for building the simulation. 
    virtual void Build() const;
    virtual void BuildForMaster() const;
};

#endif