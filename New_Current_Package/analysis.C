
#include "TFile.h"
#include "TH2.h"
#include "TNtuple.h"
#include <iostream>

void SetLeafAddress(TNtuple* ntuple, const char* name, void* address);


int analysis()
{
    gROOT->Reset();

   // Opening the file for each filename that is defined.
    TFile *file_02 = new TFile("./Data/Hits.root");

   // Pulling out the ntuple from the .root file
    TNtuple *tup_02 = (TNtuple*)file_02->Get("hits");


    int size = tup_02->GetEntries();

    int scor_vol;
    double eng_dep;


    SetLeafAddress(tup_02, "VolumeCopyNo.", &scor_vol);
    SetLeafAddress(tup_02, "EnergyDep", &eng_dep);



    std::vector<int> scoringvols;
    std::vector<double> energydep;

    for(int i = 0; i<size; i++){

        tup_02->GetEntry(i);
        scoringvols.push_back(scor_vol);
        eng_dep.push_back(energydep);

    }

}


void SetLeafAddress(TNtuple* ntuple, const char* name, void* address) {
  TLeaf* leaf = ntuple->FindLeaf(name);
  if ( ! leaf ) {
    std::cerr << "Error in <SetLeafAddress>: unknown leaf --> " << name << std::endl;
    return;
  }
  leaf->SetAddress(address);
}