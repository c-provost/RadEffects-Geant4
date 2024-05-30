#include "Dose.hh"

DoseInformation::DoseInformation(G4int NumLayers)
{
    // Initialize a vector corresponing to the number of scoring layers
    DoseValues = std::vector<G4double>(NumLayers);
}

DoseInformation::~DoseInformation() {}

void DoseInformation::AddDose(G4int index, G4double dose)
{  
    // Updating the dose value at the specific index
    DoseValues[index] += dose;
}
std::vector<G4double> DoseInformation::GetValues()
{
    // Returns the dose values (intended to be used at the end of a run);
    return DoseValues;
}