#include "RadPackRunAction.hh"


#include <fstream>

#include "G4AccumulableManager.hh"
#include "RadPackConstruction.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4AccumulableManager.hh"


RadPackRunAction::RadPackRunAction()
{
	// The default save file name for the data that gets output at the en d of the run. 
	SaveFileName = "Hits.root";

    G4AnalysisManager* man = G4AnalysisManager::Instance();


	numscoringlayers = 60;


   // Here is where the chunk of code that opens the files under the savefilename.
}

RadPackRunAction::~RadPackRunAction()
{  }

void RadPackRunAction::BeginOfRunAction(const G4Run* run)
{
	//Calling the analysis manager
	G4AnalysisManager* man = G4AnalysisManager::Instance();

	// Setting the Dose values to zero at the beginning of the run. 
	// Gets reset for each run.
	
	man->OpenFile(SaveFileName);

	man->CreateNtuple("hits", "hits");
	man->CreateNtupleIColumn("VolumeCopyNo.");
	man->CreateNtupleDColumn("EnergyDep");

	man->FinishNtuple(0);
	
}

void RadPackRunAction::EndOfRunAction(const G4Run* run)
{
	// Calling analysis manager at end of run
	G4AnalysisManager* man = G4AnalysisManager::Instance();

    man->Write();
    man->CloseFile();
}

void RadPackRunAction::SetSaveFileName(G4String savefilename)
{
    SaveFileName = savefilename;
}