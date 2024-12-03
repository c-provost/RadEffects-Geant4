// Geant4 Source Code
#include "G4Types.hh"
#include "G4RunManagerFactory.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4TransportationManager.hh"
#include "G4PVPlacement.hh"
#include "G4Box.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
//#include "G4GDMLParser.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "FTFP_BERT.hh"
#include "QGSP_BERT_HP.hh"

#include "RadPackConstruction.hh"
#include "RadPackActionInitialization.hh"
#include "RadPackPhysList.hh"
#include "RadPackGeometryMessenger.hh"


#include <random>
#include <chrono>
//#include <sys/time.h>
#include <time.h>


// ****************
//  The Geant4 Main Routine for - RadiationPackage - A simulation to predict dosages at and near the surfaces of microchips
//  subjected to space radiation. Specifically with the intent of understanding how geometries near a device can affect the
//  measured dose values. 
//
//  *********
int main(int argc, char** argv)
{
    G4cout << "Geant4 Simulation Executing!" << G4endl;
    G4cout << "<projectTitle>: RadiationPackage" << G4endl;
   // Creating new G4UIExec and RunManager objects. These are critical to the 
    G4UIExecutive* ui = 0;
    G4RunManager *theRunManager = new G4RunManager();
    G4UImanager* UImanager = G4UImanager::GetUIpointer();


//    // Setting random engine and seed
     struct timeval tt;
     auto pid = getpid();
     auto a = std::chrono::system_clock::now();

     time_t b = std::chrono::system_clock::to_time_t(a);

     long int timeint = static_cast<long int> (b);

     long timeSeed = timeint + pid*3137; // different machines, same time --> different seed
     timeSeed = std::abs(timeSeed); // take only positive seeds.
     G4cout << "<randomSeed>: " << timeSeed << G4endl;

   // Setting Random Generator
    CLHEP::HepRandom::setTheEngine( new CLHEP::HepJamesRandom );
  	CLHEP::HepRandom::setTheSeed( timeSeed );


   // Creating new RadiationDetectorConstruction object
    RadiationDetectorConstruction* theDetectorConstruction = new RadiationDetectorConstruction();

    RadPackDetectorMessenger *theMess = new RadPackDetectorMessenger(theDetectorConstruction);
    theRunManager->SetUserInitialization(theDetectorConstruction);
    theRunManager->SetUserInitialization(new RadPackPhysList());
    theRunManager->SetUserInitialization(new RadPackActionInitialization());

    UImanager->ApplyCommand("/control/execute Particle.mac");
    
   // Telling the run manager that these configurations of the system are final. Proceed to run
    theRunManager->Initialize();
   // If the executbale command is not given an input file to run
    if (argc == 1)
    {
       // Creating a new UI Executive
        ui = new G4UIExecutive(argc, argv);
    }
    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();

    G4cout << "this file" << G4endl;
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
    delete theRunManager;

    return 0;
}