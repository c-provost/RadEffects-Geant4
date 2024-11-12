#include <iostream>
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "ConstructWorld.hh"
#include "PhysList.hh"
#include "Action.hh"
#include "Physics.hh"
#include "DetectorMessenger.hh"

#include "Randomize.hh"
#include <sys/unistd.h>
#include <sys/time.h>
#include <time.h>

int main(int argc, char** argv)
{
    int returncode = system("clear");
    G4cout << "Welcome to your Geant4 Simulation!" << G4endl << "Glad to have you here!" << G4endl;
    G4UIExecutive* ui = 0;

   // Choose the Random engine
  	struct timeval tt;
  	auto pid = getpid();
  	gettimeofday(&tt,NULL);
  	long timeSeed = tt.tv_sec*1000+(tt.tv_usec/1000);
  	timeSeed += pid*3137; //different machines, same time --> different seed
  	timeSeed = std::abs(timeSeed); //take only positive seeds.
  	G4cout << "Setting random seed: " << timeSeed << G4endl;
  //
  // Set Random generator
  	CLHEP::HepRandom::setTheEngine( new CLHEP::HepJamesRandom );
  	CLHEP::HepRandom::setTheSeed( timeSeed );


    MyDetectorConstruction* detConst = new MyDetectorConstruction();
    PackageDetectorMessenger* detMess = new PackageDetectorMessenger(detConst);
    G4RunManager* runManager = new G4RunManager();

    runManager->SetUserInitialization(detConst);
    runManager->SetUserInitialization(new PhysList());
    runManager->SetUserInitialization(new ActionInitialization());

    runManager->Initialize();
    
    if (argc == 1)
    {
        ui = new G4UIExecutive(argc, argv);
    }

    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();

    G4UImanager * UImanager = G4UImanager::GetUIpointer();

    if (ui)
    {
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
    }
    else
    {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }

    delete visManager;
    delete runManager;
    //delete detMess;

    G4cout << "\n" << "Simulation Completed " << G4endl
            << "Thanks for your time 😸" << "\n\n";
    return 0;
}