#include "PhysList.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4SystemOfUnits.hh"
#include "G4EmParameters.hh"

#include "G4MicroElecElastic.hh"
#include "G4MicroElecElasticModel_new.hh"

#include "G4MicroElecInelasticModel_new.hh"

#include "G4VEmModel.hh"

#include "G4LossTableManager.hh"
#include "G4EmConfigurator.hh"

#include "G4UniversalFluctuation.hh"

PhysList::PhysList() : G4VModularPhysicsList()
{
    SetDefaultCutValue(.5 * micrometer);
    SetVerboseLevel(1);

    fEmPhysicsList = new G4EmStandardPhysics_option4();
    G4ProductionCutsTable::GetProductionCutsTable()->
        SetEnergyRange(800 * eV, 1*GeV);

    G4EmParameters* param = G4EmParameters::Instance();
    param->SetMinEnergy(800*eV);
    param->SetMaxEnergy(1 * GeV);
}

PhysList::~PhysList()
{ delete fEmPhysicsList; }

void PhysList::ConstructParticle()
{
    fEmPhysicsList->ConstructParticle(); 
}

void PhysList::ConstructProcess()
{
    AddTransportation();
    fEmPhysicsList->ConstructProcess();
    G4EmParameters* param = G4EmParameters::Instance();
}