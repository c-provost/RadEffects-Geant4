// Generator Action File
#include "RadPackGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "G4Electron.hh"

RadPackGeneratorAction::RadPackGeneratorAction() : G4VUserPrimaryGeneratorAction()
{
    // Initializing the particlecounter object
        primarycounter = 0;
        chunkprims = 0;
    // Creating the Particle Source
        fParticleSource = new G4GeneralParticleSource();
    // Defining the Primary Particle
        fParticleSource->SetParticleDefinition(G4Electron::Definition());
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RadPackGeneratorAction::~RadPackGeneratorAction(){ delete fParticleSource; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RadPackGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    // Incrementing the particlecounter;
        primarycounter++;
        if(primarycounter == 500000)
        {   
            primarycounter = 0;
            chunkprims++; 
            G4cout <<  "<500K Primaries Generated (Sim Lifetime): " << chunkprims << ">" << G4endl;
        }
    // Creating a primary particle and sending it off. 
        fParticleSource->GeneratePrimaryVertex(anEvent);

}