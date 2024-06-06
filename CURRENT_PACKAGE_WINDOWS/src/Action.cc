#include "Action.hh"

ActionInitialization::ActionInitialization() {  }

ActionInitialization::~ActionInitialization()  {    }

void ActionInitialization::Build() const
{
    // Creating a new particle source object
    MyGenerator* generator = new MyGenerator();
    SetUserAction(generator);
    // Creating a runaction object
    RunAction* runAction = new RunAction();
    SetUserAction(runAction);
    // Creating an event action object
    EventAction* eventAction = new EventAction(runAction);
    SetUserAction(eventAction);
    // Creating a stepAction object
    SteppingAction* stepAction = new SteppingAction(eventAction);
    SetUserAction(stepAction);
}
void ActionInitialization::BuildforMaster() const
{
    // The build method for multithreading mode. 
    // I do not regularly use this, as the interfacing with other objects
    // Causes seg fualts, and data-writing errors. Future project? -CP Jun 4 2024
    RunAction* runAction = new RunAction();
    SetUserAction(runAction);
}