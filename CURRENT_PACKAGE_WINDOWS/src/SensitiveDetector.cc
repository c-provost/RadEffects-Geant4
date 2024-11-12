#include "SensitiveDetector.hh"
#include "G4Step.hh"

PackSensitiveDetector::PackSensitiveDetector(G4String detName) : G4VSensitiveDetector(name)
{
    std::cout << "Sensitive Detector Object Created! \n         <name>: " << detName << G4endl;
}

PackSensitiveDetector::~PackSensitiveDetector()
{}

G4book PackSensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory* theHist)
{
    G4double theEng = aStep->GetTotalEnergyDeposit();


    



}