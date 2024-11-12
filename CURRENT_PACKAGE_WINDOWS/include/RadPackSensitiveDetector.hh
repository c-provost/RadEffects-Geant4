#ifndef sensitivedet_hh
#define sensitiedet_hh

#include "G4VSensitiveDetector.hh"
#include "globals.hh"

class PackSensitiveDetector :: public G4VSensitiveDetector
{
    public:
   // The constructor for the detector - inherits from the G4VSensitiveDetector Constructor
    PackSensitiveDetector(G4String name);
    ~PackSensitiveDetector();

    private:
   // The method called for every step taken in the material.
    virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* tHist);
}

#endif