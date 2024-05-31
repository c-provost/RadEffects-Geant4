#include "run.hh"
#include "G4AccumulableManager.hh"
#include "ConstructWorld.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4AccumulableManager.hh"


#include "event.hh"

RunAction::RunAction()
{
	doseinfo = new DoseInformation(62);
    G4AnalysisManager* man = G4AnalysisManager::Instance();
	G4cout << "The location of the dose values is " << &Dose_values << G4endl;

	numscoringlayers = 60;
	for(int i = 1; i < numscoringlayers + 1; i++){
		std::string my_chunk;
		if(i < 10)
		{
			my_chunk = "Slice_0";
		}
		else
		{
			my_chunk = "Slice_";
		}
	
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
{}

void RunAction::BeginOfRunAction(const G4Run* run)
{
	// Setting the Dose values to zero at the beginning of the run. 
	// Gets reset for each run.
	for (int i = 0; i<numscoringlayers + 2; i++)
		{ Dose_values[i] = 0; }

	allthedoses = 0.;
	
	myvalues = std::vector<G4double>(62);
    G4AnalysisManager* man = G4AnalysisManager::Instance();
	
	G4int RunID = run->GetRunID();

	std::stringstream strRunID;
	strRunID << RunID;

	man->OpenFile("output"+strRunID.str()+".csv");


}

void RunAction::EndOfRunAction(const G4Run*)
{
	G4cout << "Run Complete!" << G4endl;
	G4AnalysisManager* man = G4AnalysisManager::Instance();
	std::vector<G4double> finaldosevals = doseinfo->GetValues();

	for(int i=0; i<numscoringlayers + 2; i++)
	{	
		man->FillNtupleDColumn(numscoringlayers + 2, i, finaldosevals[i]);
		G4cout << "The Dose in Layer " << std::to_string(i) << " is " << finaldosevals[i] << G4endl; 
	}

	man->AddNtupleRow(numscoringlayers + 2);

	man->Write();
	man->CloseFile();

	G4cout << G4endl << "The amount of accumulated primaries in over layer for THIS RUN is " << primarycounter << G4endl << G4endl;
	primarycounter = 0;

}
void RunAction::primaryinoverlayercounter()
{
	primarycounter += 1;
}

DoseInformation* RunAction::GetDoseInfo()
{
	return doseinfo;
}
