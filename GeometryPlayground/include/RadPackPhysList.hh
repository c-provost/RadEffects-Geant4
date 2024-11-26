#ifndef PLIST_HH
#define PLIST_HH

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class G4VPhysicsConstructor;

class RadPackPhysList : public G4VModularPhysicsList
{
public:
    RadPackPhysList();
    ~RadPackPhysList() override;

    void ConstructParticle() override;
    void ConstructProcess() override;

private: 
    G4VPhysicsConstructor* fEmPhysicsList = nullptr;

};


#endif