#include "RadPackActionInitialization.hh"
#include "RadPackGeneratorAction.hh"
#include "RadPackRunAction.hh"


RadPackActionInitialization::RadPackActionInitialization() {}

RadPackActionInitialization::~RadPackActionInitialization() {}

void RadPackActionInitialization::Build() const {
   // Creating user action classes that are sent to the simulation guts. 
    SetUserAction(new RadPackGeneratorAction);
    RadPackRunAction* theRunAction = new RadPackRunAction();

    SetUserAction(theRunAction);
}

void RadPackActionInitialization::BuildForMaster() const
{
   // The build method for multithreading mode. 
   // I do not regularly use this, as the interfacing with other objects
    RadPackRunAction* theRunAction = new RadPackRunAction();
    SetUserAction(theRunAction);
}