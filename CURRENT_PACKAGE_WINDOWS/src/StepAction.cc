#include "StepAction.hh"

SteppingAction::SteppingAction(EventAction* eventAction)
{
    // Storing so there is access to the event routines
    fEventAction = eventAction;
}
SteppingAction::~SteppingAction()
{}
void SteppingAction::UserSteppingAction(const G4Step* step)
{
    G4int numscoringlayers = 60;


    // The volume that the particle is in before the step is taken.
    G4LogicalVolume* const volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

    // Detector Construction object to access volume information
    const MyDetectorConstruction* detectorConstruction = static_cast<const MyDetectorConstruction*> (G4RunManager::GetRunManager()
                                    ->GetUserDetectorConstruction());

    // Logical volumes for non-scoring layers. 
    G4LogicalVolume *fbot    = detectorConstruction->GetVolumeBot();
    G4LogicalVolume *flid    = detectorConstruction->GetVolumeLid();
    G4LogicalVolume *fOverLayer  = detectorConstruction->GetVolumeOverlayer();

    // Getting logic information 
    G4LogicalVolume* prestepVol = volume;
    G4VPhysicalVolume* postStepVol_phys = step->GetPostStepPoint()->GetTouchableHandle()->GetVolume();
    G4LogicalVolume* postStepVol;

    // The first scoring layer, but the target volume may change depending on application.
    G4LogicalVolume* targetvolume = detectorConstruction->GetScoringVolumes(1);

    //********** This logic needs updating - shouldn't be this many if statements nested **********\\
    // Asking if the particle is a primary particle
    if (step->GetTrack()->GetParentID() == 0)
    {
        // Asking if the particle is still in the world volume
        if (postStepVol_phys != 0)
        {
            postStepVol = postStepVol_phys->GetLogicalVolume();
            // Asking if the volume has changed
            if (prestepVol != postStepVol)
            {
                // 'Is my new location the front of the chip?'
                if (postStepVol == targetvolume)
                {
                    // Getting the pre and post-step z values. 
                    G4double pt1 = step->GetPostStepPoint()->GetPosition().z();
                    G4double pt0 = step->GetPreStepPoint()->GetPosition().z();
                    // Determining the direction the primary is approaching from
                    G4double zdir = pt1 - pt0;
                    // Asking if the direction of motion is positive. 
                    if (zdir > 0)
                    {
                        // Here is where our messenging happens.
                        fEventAction->primaryinoverlayercounter();
                    }
                }
            }
        }
    }
    // Calculating the energy deposited in the step
    G4double edep = step->GetTotalEnergyDeposit();

    // Determing which logical volume the energy was deposited in - then sending that information to the event handler
    if (volume == fbot)
    {
        fEventAction->addEnergydepBot(edep);
    }

    if (volume == flid)
    {
        fEventAction->addEnergydepLid(edep);
    }

    for (int i = 1; i < (numscoringlayers + 1); i++)
    {  
        if(volume == (detectorConstruction->GetScoringVolumes(i)))
        {
            fEventAction->addEnergydep(i, edep);
        }
    }

}