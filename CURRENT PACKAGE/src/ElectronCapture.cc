#include "ElectronCapture.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4Electron.hh"


G4ElectronCapture::G4ElectronCapture(const G4String& regName, G4double ekinlim) :
                                G4VDiscreteProcess("eCapture", fElectromagnetic), kinEnergyThreshold(ekinlim),
                                regionName(regName), region(0)
         {
            if(regName == "" || regName == "world)"){
                regionName = "DefaultRegionForTheWorld";
            }    
            pParticleChange = &fParticleChange;            
         }

G4ElectronCapture::~G4ElectronCapture()
{}

void G4ElectronCapture::SetKinEnergyLimit(G4double val)
{
  kinEnergyThreshold = val;
  if(verboseLevel > 0) {
    G4cout << "### G4ElectronCapture: Tracking cut E(MeV) = " 
	   << kinEnergyThreshold/MeV << G4endl;
  }
}

void G4ElectronCapture::BuildPhysicsTable(const G4ParticleDefinition&)
{
  region = (G4RegionStore::GetInstance())->GetRegion(regionName);
  if(region && verboseLevel > 0) {
    G4cout << "### G4ElectronCapture: Tracking cut E(MeV) = " 
	   << kinEnergyThreshold/MeV << " is assigned to " << regionName 
	   << G4endl;
  }
}

G4bool G4ElectronCapture::IsApplicable(const G4ParticleDefinition&)
{ return true; }

G4double 
G4ElectronCapture::PostStepGetPhysicalInteractionLength(const G4Track& aTrack,
G4double, G4ForceCondition* condition)
{
    *condition = NotForced;

    G4double limit = DBL_MAX;
    if(region)
    {
        if(aTrack.GetVolume()->GetLogicalVolume()->GetRegion() == region && 
        aTrack.GetKineticEnergy() < kinEnergyThreshold) {limit = 0.0; }
    }
    return limit;
}

G4VParticleChange* G4ElectronCapture::PostStepDoIt(const G4Track& aTrack,
const G4Step&)
{
    pParticleChange->Initialize(aTrack);
    pParticleChange->ProposeTrackStatus(fStopAndKill);
    pParticleChange->ProposeLocalEnergyDeposit(aTrack.GetKineticEnergy());
    fParticleChange.SetProposedKineticEnergy(0.0);
    return pParticleChange;
}


G4double G4ElectronCapture::GetMeanFreePath(const G4Track&, G4double,
G4ForceCondition*)
{
    return DBL_MAX;
}

