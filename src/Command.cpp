#include "Command.h"

Command::Command()
{ // default constructor
    this->command = nullptr;
    this->effect = nullptr;
}

Command::Command(string& com, string& eff)
{ // parametrized constructor
    this->command = new string(com);
    this->effect = new string(eff);
}

Command::Command(const Command &c)
{ // copy constructor
    this->command = new string(*(c.command));
    this->effect = new string(*(c.effect));
}

Command::~Command()
{
    delete command;
    delete effect;
}

void Command::saveEffect(string eff)
{
    if (effect) {
        *effect = eff; // Update the existing string
    } else {
        effect = new string(eff); // If effect is nullptr, create a new string
    }
    notify(this);
}

string Command::stringToLog(){
    string returnString = "The command's effect is: " + getEffect();
    return returnString;
}