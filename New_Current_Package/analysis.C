
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

   int numfiles = 1;

   std::vector<TFile*> the_files;
   std::vector<TNtuple*> the_tuples;
    std::vector<int> tuple_sizes;

   // Looping through the number of volumes and assigning the corresponding file to an index in the vector
   for(int i = 0; i<numfiles; i++)
   {
    string str1;
      if(i<9)
      {
        str1 = "./data/primaryRun_0";
      }
      else{ str1 = "./data/primaryRun_"; }

      string str2 = std::to_string(i+1);
      string str3 = ".root";

      string titlestr = str1 + str2 + str3;
      const char *thetitle = titlestr.c_str();

      the_files.push_back(new TFile(thetitle));
   }

  // Filling the tuple vector with the tuples in each file
  for(TFile* val : the_files)
  {
    TNtuple* theFileTup = (TNtuple*)val->Get("hits");
    the_tuples.push_back(theFileTup);
    tuple_sizes.push_back(theFileTup->GetEntries());
  }

   // These are variables whose addresses will be updated based on location in the vector.
    int scor_vol;
    double eng_dep;

   // The vectors that will get filled with the data from the histogram in the root file
    std::vector<int> scoringvols;
    std::vector<double> energydep;

  for(int i = 0; i<numfiles; i++)
  {
    TNtuple* val = the_tuples[i];
    SetLeafAddress(val, "VolumeCopyNo.", &scor_vol);
    SetLeafAddress(val, "EnergyDep", &eng_dep);

    for(int j = 0; j<tuple_sizes[i]; j++)
    {
      std::cout << j << std::endl;
      val->GetEntry(j);
      scoringvols.push_back(scor_vol);
      energydep.push_back(eng_dep);
    }
  }


   // These are change-able figures that allow for the manipulation of data. They will change the structure of the 
    int numcols = 20;
    double lowval = 0.5;
    double highval = 20.5;

   // The mass of the scoring layers. This should be updated elsewhere in this file.
    double mass_g = 10;

    TH1 *eDepHist = new TH1D("Dose (rad)", "Dose (rad)", numcols, lowval, highval);

    for(int i=0; i<energydep.size(); i++)
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