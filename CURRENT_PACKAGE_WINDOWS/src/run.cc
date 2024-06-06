#include "run.hh"
#include "event.hh"

#include <fstream>

#include "G4AccumulableManager.hh"
#include "ConstructWorld.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4AccumulableManager.hh"

RunAction::RunAction()
{
    G4AnalysisManager* man = G4AnalysisManager::Instance();

	numscoringlayers = 60;

	// Creating all the ntuples to which data will be written
	// NOTE! - Sans the total dose files, these do not get written to (we only care about the dose data anyways) -CP Jun. 4 2024
	for(int i = 1; i < numscoringlayers + 1; i++){
		// Namiing the File for each Scoring Layer
		std::string my_chunk;

		if(i < 10) {	my_chunk = "Slice_0";	}
		else   {	my_chunk = "Slice_";	}
	
		std::string my_num = std::to_string(i);
		std::string my_title = my_chunk + my_num;

		man->CreateNtuple(my_title, my_title);
		man->CreateNtupleDColumn("Deposit#");
		man->CreateNtupleDColumn("fEdep");
		man->CreateNtupleDColumn("Dose_Rad_Si");
		man->CreateNtupleDColumn("Total_Edep");
		man->CreateNtupleDColumn("Total_Dose");
		man->CreateNtupleDColumn("AvgEdep");
		man->CreateNtupleDColumn("AvgDose");
		man->FinishNtuple(i-1);
	}

	// Information Ntuple for the lid
	man->CreateNtuple("Info_Lid", "Info_Lid");
	man->CreateNtupleDColumn("Deposit#");
	man->CreateNtupleDColumn("fEdep");
	man->CreateNtupleDColumn("Dose_Rad_Si");
	man->CreateNtupleDColumn("Total_Edep");
	man->CreateNtupleDColumn("Total_Dose");
	man->CreateNtupleDColumn("AvgEdep");
	man->CreateNtupleDColumn("AvgDose");
	man->FinishNtuple(numscoringlayers);

	// Information Ntuple for the bottom
	man->CreateNtuple("Info_bot", "Info_bot");
	man->CreateNtupleDColumn("Deposit#");
	man->CreateNtupleDColumn("fEdep");
	man->CreateNtupleDColumn("Dose_Rad_Si");
	man->CreateNtupleDColumn("Total_Edep");
	man->CreateNtupleDColumn("Total_Dose");
	man->CreateNtupleDColumn("AvgEdep");
	man->CreateNtupleDColumn("AvgDose");
	man->FinishNtuple(numscoringlayers + 1);

	// Total dose for all componenets
	man->CreateNtuple("Total Dose", "Total Dose");
	man->CreateNtupleDColumn("Lid");
	for (int i = 1; i < numscoringlayers + 1; i++)
	{
		G4String my_chunk;
		if(i < 10) { my_chunk = "Dose_0"; }
		else       { my_chunk = "Dose_";  }

		G4String my_num = std::to_string(i);
		man->CreateNtupleDColumn(my_chunk + my_num);
	}
	man->CreateNtupleDColumn("Bottom");
	man->FinishNtuple(numscoringlayers + 2);
}

RunAction::~RunAction()
{  }

void RunAction::BeginOfRunAction(const G4Run* run)
{
	//Calling the analysis manager
	G4AnalysisManager* man = G4AnalysisManager::Instance();

	// Setting the Dose values to zero at the beginning of the run. 
	// Gets reset for each run.
	for (int i = 0; i<numscoringlayers + 2; i++)
		{ Dose_values[i] = 0; }
	
	//Gathering Run info - file-naming.
	G4int RunID = run->GetRunID();
	std::stringstream strRunID;
	strRunID << RunID;
	man->OpenFile("output"+strRunID.str()+".csv");
}

void RunAction::EndOfRunAction(const G4Run* run)
{
	// Calling analysis manager at end of run
	G4AnalysisManager* man = G4AnalysisManager::Instance();

	// Writing to ntuple the dose information for each scoring layer
	for(int i=0; i<numscoringlayers + 2; i++)
	{	
		man->FillNtupleDColumn(numscoringlayers + 2, i, Dose_values[i]);
		G4cout << "The Dose in Layer " << std::to_string(i) << " is " << Dose_values[i] << G4endl; 
	}
	// Updating ntuple
	man->AddNtupleRow(numscoringlayers + 2);
	man->Write();
	man->CloseFile();

	// Gathering Run information - for file writing.
    G4int RunID = run->GetRunID();
	std::stringstream strRunID;
	strRunID << RunID;

	// Creating primary log if it doesn't already exist
	std::fstream primarylog;
    if(fopen("primarylog.txt", "r") == NULL)
    {
		// Using standard file-writing C++. Opening file in append mode
        primarylog.open("primarylog.txt", std::fstream::app);
        primarylog << "PRIMARY COUNTER LOG FOR SIMULATION" << std::endl;
        primarylog << "Run No.  Primary Count";
        primarylog.close();
    }
	// Writing the number of primaries to the primarylog.txt file
    primarylog.open("primarylog.txt", std::fstream::app);
    primarylog << "\n" << strRunID.str() << "  " << std::to_string(primarycounter) << std::endl;

	// Resetting the primaries at end of run
	primarycounter = 0;
	G4cout << "Run Complete!" << G4endl;
}
void RunAction::primaryinoverlayercounter()
{
	// Method that gets called from the event. Adds if a primary enters the overlayer
	primarycounter += 1;
}

void RunAction::AddDose(G4int i, G4double dosevalue)
{
	// Dose addition value that gets called from the event. 
	// Adds does information to the index in the array that corresponds to the scoring layer
	// Holds the scoring layer and lid information, with the lid and bottom being the first and last
	// Indicies respectively.
	Dose_values[i] += dosevalue;
}