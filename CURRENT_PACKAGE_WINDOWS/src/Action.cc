#include "Action.hh"

ActionInitialization::ActionInitialization()
{}

ActionInitialization::~ActionInitialization()
{}

void ActionInitialization::Build() const
{
    MyGenerator* generator = new MyGenerator();
    SetUserAction(generator);

    RunAction* runAction = new RunAction();
    SetUserAction(runAction);

    EventAction* eventAction = new EventAction(runAction);
    SetUserAction(eventAction);

    SteppingAction* stepAction = new SteppingAction(eventAction);
    SetUserAction(stepAction);

    G4cout << "A thing has been done!!" << "\n";

}

void ActionInitialization::BuildforMaster() const
{
    RunAction* runAction = new RunAction();
    SetUserAction(runAction);
}

