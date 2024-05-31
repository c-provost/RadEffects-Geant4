#ifndef PLIST_HH
#define PLIST_HH

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class G4VPhysicsConstructor;

class PhysList : public G4VModularPhysicsList
{
public:
    PhysList();
    ~PhysList() override;

    void ConstructParticle() override;
    void ConstructProcess() override;

private: 
    G4VPhysicsConstructor* fEmPhysicsList = nullptr;

};


#endif