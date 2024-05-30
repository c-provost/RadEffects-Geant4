#ifndef GUN_HH
#define GUN_HH

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4SystemofUnits.hh"
#include "G4ParticleTable.hh"
#include "G4Geantino.hh"
#include "G4IonTable.hh"

class MyGenerator : public G4VUserPrimaryGeneratorAction
{
public:
    MyGenerator();
    ~MyGenerator();

    virtual void GeneratePrimaries(G4Event*);

    G4double ThetaPicker(G4double, G4double);

private:
    G4ParticleGun* fParticleGun;

};



#endif