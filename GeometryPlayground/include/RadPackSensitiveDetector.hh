#ifndef sensitivedet_hh
#define sensitivedet_hh

#include "G4VSensitiveDetector.hh"
#include "globals.hh"

#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"

class RadPackSensitiveDetector : public G4VSensitiveDetector
{
    public:
   // The constructor for the detector - inherits from the G4VSensitiveDetector Constructor
    RadPackSensitiveDetector(G4String name);
    ~RadPackSensitiveDetector();

    private:
   // The method called for every step taken in the material.
    virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* tHist);
    

    G4AnalysisManager* man;
};

#endif