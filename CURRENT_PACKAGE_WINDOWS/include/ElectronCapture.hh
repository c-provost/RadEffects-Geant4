#ifndef ElectronCapture_hh
#define ElectronCapture_hh

#include "G4VDiscreteProcess.hh"
#include "globals.hh"
#include "G4ParticleChangeForGamma.hh"

class G4Region;

class G4ElectronCapture : public G4VDiscreteProcess
{
public:
    G4ElectronCapture(const G4String& regName, G4double ekinlimit);

    virtual ~G4ElectronCapture();

    void SetKinEnergyLimit(G4double);
    
    virtual void BuildPhysicsTable(const G4ParticleDefinition&);

    virtual G4bool    IsApplicable(const G4ParticleDefinition&);

    virtual G4double PostStepGetPhysicalInteractionLength( const G4Track& track,
                                     G4double previousStepSize,
                                     G4ForceCondition* condition);
    virtual G4VParticleChange* PostStepDoIt(const G4Track&, const G4Step&);

protected:
    virtual G4double GetMeanFreePath(const G4Track&, G4double, G4ForceCondition*);

private:
    G4ElectronCapture(const G4ElectronCapture&);

    G4ElectronCapture& operator = (const G4ElectronCapture &right);

    G4double kinEnergyThreshold;
    G4String regionName;
    G4Region* region;
    G4ParticleChangeForGamma fParticleChange;

};

#endif