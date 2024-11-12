#ifndef PrimaryGeneratorAction_hh
#define PrimaryGeneratorAction_hh

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "globals.hh"

class G4Event;

class RadPackGeneratorAction : public G4VUserPrimaryGeneratorAction
{
    public:
    // Constructor and Destructor
        RadPackGeneratorAction();
        ~RadPackGeneratorAction();
    // Public method inherited from PrimaryGeneratorAction object, 
    // gets called at the BeamOn method from Run.
        void GeneratePrimaries(G4Event* anEvent) override;

    private:
    // General Particle Source oject, can be used to create 
    // Special source geometries, energies. Customizeable.
        G4GeneralParticleSource* fParticleSource = nullptr;
    // Counter used for macro-level monitoring of total primaries created.
        G4int primarycounter, chunkprims;
};

#endif