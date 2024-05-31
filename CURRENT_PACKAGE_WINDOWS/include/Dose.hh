#ifndef DOSE_HH
#define DOSE_HH

#include "globals.hh"
#include<vector>


// A class Designed to store and Accumulate dose information on the run-level. 
// I don't know if it works yet, but there is promise. *CP - Jan 30, 2024
class DoseInformation
{
public:
    DoseInformation(G4int numlayers);
    ~DoseInformation();

    void AddDose(G4int index, G4double dose);

    std::vector<G4double> GetValues();

private:
    std::vector<G4double> DoseValues;

};

#endif