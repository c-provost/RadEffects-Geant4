
#ifndef Physics_HH
#define Physics_HH

#include "G4VModularPhysicsList.hh"

#include "G4EmPenelopePhysics.hh"
#include "G4OpticalPhysics.hh"


class Physico : public G4VModularPhysicsList
{
public:
    Physico();
    ~Physico();
};

#endif