
#include "TFile.h"
#include "TH2.h"
#include "TNtuple.h"
#include <iostream>

// this is the function that will be used to access 
// the ntuple is what is pulled fomr the .root file, the name parameter is the name of the specific leaf from the root file
// that wishes to be accessed (the specific column from the histogram). The address is the address of a variable of specific
// data type within the column. 
void SetLeafAddress(TNtuple* ntuple, const char* name, void* address);


int analysis()
{
    gROOT->Reset();

   // Opening the file for each filename that is defined.
    TFile *file_02 = new TFile("./build/primaryRun_01.root");

   // Pulling out the ntuple from the .root file
    TNtuple *tup_02 = (TNtuple*)file_02->Get("hits");

   // Finding the size of the ntuple. this index will be used for data manipulation later in this file
    int size = tup_02->GetEntries();

   // These are variables whose addresses will be updated based on location in the vector.
    int scor_vol;
    double eng_dep;

   // Setting the address of the leaf to that of the scoring volume
    SetLeafAddress(tup_02, "VolumeCopyNo.", &scor_vol);
    SetLeafAddress(tup_02, "EnergyDep", &eng_dep);


   // The vectors that will get filled with the data from the histogram in the root file
    std::vector<int> scoringvols;
    std::vector<double> energydep;

   // Looping through the data in the histogram, getting the entry from the histogram, and assigning that value
   // to the data vector. 
    for(int i = 0; i<size; i++){

        tup_02->GetEntry(i);
        scoringvols.push_back(scor_vol);
        energydep.push_back(eng_dep);
    }

   // These are change-able figures that allow for the manipulation of data. They will change the structure of the 
    int numcols = 20;
    double lowval = 0.5;
    double highval = 20.5;

   // The mass of the scoring layers. This should be updated elsewhere in this file.
    double mass_g = 10;

    TH1 *eDepHist = new TH1D("Dose (rad)", "Dose (rad)", numcols, lowval, highval);

    for(int i=0; i<size; i++)
    {
     // Converting the energy deposition (in eV) to dose in rads (100*erg/gram). There are 6.24 MeV in 100 erg.
      double dose_rad = energydep[i]/6.24/pow(10, 6)/mass_g;
      eDepHist->Fill(scoringvols[i], dose_rad);
    }

    eDepHist->Draw();


  return 0;
}


void SetLeafAddress(TNtuple* ntuple, const char* name, void* address)
{
   // Pulling the column of name 'name' from the ntuple
    TLeaf* leaf = ntuple->FindLeaf(name);
   // Error message to check whether that leaf actually exits. If not, outputs message,
   // and terminates the function call. 
    if ( ! leaf ) {
      std::cerr << "Error in <SetLeafAddress>: unknown leaf --> " << name << std::endl;
      return;
    }
   // Assigning the address of the leaf to that of the data type.
    leaf->SetAddress(address);
}