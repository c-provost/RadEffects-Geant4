#include "event.hh"
#include "G4AccumulableManager.hh"
#include "G4RunManager.hh"
#include "ConstructWorld.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

EventAction::EventAction(RunAction* runAction)
{
    fRunAction = runAction;

    // Initialzing the fEdep values. 
    fEdep_bot = 0; fEdep_lid = 0;
    for (int i = 0; i < 60; i++)
        {   fEdepScoring[i] = 0;  }
}

EventAction::~EventAction()
{  /*Desructor*/ }

void EventAction::BeginOfEventAction(const G4Event*)
{
    // Edep Values get reset at the beginning of each event
    fEdep_bot = 0; fEdep_lid = 0;
    for (int i = 0; i < 60; i++)
        {   fEdepScoring[i] = 0;  }
}

void EventAction::EndOfEventAction(const G4Event*)
{
    G4AnalysisManager* man = G4AnalysisManager::Instance();

    const MyDetectorConstruction* detectorConstruction =
        static_cast< const MyDetectorConstruction* >
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

    
    // Mass access for dose calculation
    G4double massSlice = (detectorConstruction->GetScoringVolumes(0))->GetMass();
    G4double massSlice_g = massSlice/gram;

    G4double massLid   = detectorConstruction->GetVolumeLid()->GetMass();
    G4double massLid_g = massLid/gram;

    G4double massBot   = detectorConstruction->GetVolumeBot()->GetMass();
    G4double massBot_g = massBot/gram;

    // Creating the fEdep array
    G4double fEdep_vals[62];
    fEdep_vals[0] = fEdep_lid;
    fEdep_vals[61] = fEdep_bot;

    // Setting values in the fEdep Array
    for (int i = 1; i < 61; i++)
        { fEdep_vals[i] = fEdepScoring[i -1]; }
    
    // Looping through the fEdep values of all layers
    for (int i = 0; i < 62; i++)
    {
        // Only taking the non-zero energy dep. values for the event.
        if(fEdep_vals[i] != 0)
        {   
            // Increasing the number of 'hits' for that layer
            i_counters[i] += 1;

            // Self-explanatory - taking the mass of the corresponding layer for dose calculations.
            G4double massLayer;
                 if(i ==  0){massLayer = massLid_g;}
            else if(i == 61){massLayer = massBot_g;}
            else            {massLayer = massSlice_g;}

            // converting edep to ergs. 
            G4double erg_layer = fEdep_vals[i] / 624153;

            // Calculating the dose for that specific layer (in rad)
            G4double dose_rad_si_layer = erg_layer / massLayer / 100;

            // Values in their respective arrays.
            edep_tot_list[i] = edep_tot_list[i] + fEdep_vals[i];
            dose_tot_list[i] += dose_rad_si_layer;

            edep_avg_list[i] = edep_tot_list[i] * massLayer / i_counters[i];
            dose_avg_list[i] = dose_tot_list[i] / i_counters[i];
/*
            // Updating the Ntuple (.csv file) for the corresponding layer
            man->FillNtupleDColumn(i, 0, i_counters[i]);
            man->FillNtupleDColumn(i, 1, fEdep_vals[i]);
            man->FillNtupleDColumn(i, 2, dose_rad_si_layer);
            man->FillNtupleDColumn(i, 3, edep_tot_list[i]);
            man->FillNtupleDColumn(i, 4, dose_tot_list[i]);
            man->FillNtupleDColumn(i, 5, edep_avg_list[i]);
            man->FillNtupleDColumn(i, 6, dose_avg_list[i]);
            man->AddNtupleRow(i);
*/
            // Sending dose command to the run object to accumulate dose in a separate .csv file for the entire run.
            // This could stand to be updated. 
            fRunAction->GetDoseInfo()->AddDose(i, dose_rad_si_layer);
        }
    }
}


void EventAction::primaryinoverlayercounter()
{
    fRunAction->primaryinoverlayercounter();
}