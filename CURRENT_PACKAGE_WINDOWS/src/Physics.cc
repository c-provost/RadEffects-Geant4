#include "Physics.hh"

Physico::Physico()
{
    RegisterPhysics(new G4EmPenelopePhysics());
    RegisterPhysics(new G4OpticalPhysics());
}

Physico::~Physico()
{}
