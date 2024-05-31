#define _USE_MATH_DEFINES
#include "ParticleGun.hh"

#include<iostream>
#include<cmath>
#include<math.h>
#include<random>



MyGenerator::MyGenerator()
{
    fParticleGun = new G4ParticleGun(1);

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();

    G4ParticleDefinition* particle = particleTable->FindParticle("gamma");


    G4ThreeVector pos(0, 0, -30.48 * cm);

    
    G4ThreeVector mom(0., 0., 1);      // Default momentum direction.

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);

    fParticleGun->SetParticleMomentum(1.33 * MeV);
    fParticleGun->SetParticleDefinition(particle);

}

MyGenerator::~MyGenerator()
{   delete fParticleGun;   }

void MyGenerator::GeneratePrimaries(G4Event* anEvent)
{
    // This line of code sets a uniform spherical distribution of momentum within
    // reasonable bounds for entering the 'start' hole in the collimator. 


    std::random_device rd;  // random engine
    std::uniform_real_distribution<double> dist(0.0, 1.0); // Basically an array of values
    
    
    double rand1 = dist(rd);  // randomly picking values within the array
    double rand2 = dist(rd);

    G4double theta = M_PI_2 + ThetaPicker(31., 5.5);

    G4double maxphi = std::atan(5.5 / 31.);
    
    G4double phi   = -1 * maxphi + 2 * rand2 * maxphi;
    G4double r = 31.;
    
    G4double myx =      std::sin(theta) * std::sin(phi);
    G4double myz =      std::sin(theta) * std::cos(phi);
    G4double myy =      std::cos(theta);

    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(myx, myy, myz));

    G4ParticleDefinition* particle = fParticleGun->GetParticleDefinition();

    //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., -1));
    fParticleGun->GeneratePrimaryVertex(anEvent);

}

G4double MyGenerator::ThetaPicker(G4double distance, G4double ydim)
{
    // Outputs an output array of Thetas that are distributed such that the
    // spherical array of output particles is uniformely distributed.

    std::random_device rd;
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    G4double maxangle = std::atan(ydim/distance);

    double myrandU = dist(rd);

    // Sweeping through an angle that is 2x the maximum angle (negative to positive)
    double myTheta = -1 * maxangle + myrandU * maxangle * 2;

    double myrandV = dist(rd);

    if(myrandV <= std::cos(myTheta))
    {
        return myTheta;
    }
    else
    {
        // Will keep going until the above if statement is true.
        return ThetaPicker(distance, ydim);
    }
}
