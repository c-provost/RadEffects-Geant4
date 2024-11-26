#include "RadPackSensitiveDetector.hh"


RadPackSensitiveDetector::RadPackSensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{
    std::cout << "Sensitive Detector Object Created! \n         <name>: " << name << G4endl;
    man = G4AnalysisManager::Instance();
}

RadPackSensitiveDetector::~RadPackSensitiveDetector()
{}

G4bool RadPackSensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory* theHist)
{
   // Obtaining the energy that the particle deposits along its path. 
    G4double theEng = aStep->GetTotalEnergyDeposit();

    G4double theEng_eV = theEng / eV;

    G4int theCopyNo = aStep->GetTrack()->GetTouchableHandle()->GetVolume()->GetCopyNo();
    
    //G4cout << "copyNo: " << theCopyNo << G4endl;
    

   // Filling the ntuple with the 
    man->FillNtupleIColumn(0, 0, theCopyNo);
    man->FillNtupleDColumn(0, 1, theEng_eV);
    man->AddNtupleRow(0);


    return true;
}