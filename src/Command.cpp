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
    this->command = c.command;
    this->effect = c.effect;
}

Command::~Command()
{
    delete command;
    delete effect;
}

void Command::saveEffect(string eff)
{
    this->effect = new string(eff);
}

