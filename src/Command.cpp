#include "Command.h"

Command::Command()
{ // default constructor
    this->command = "";
    this->effect = "";
}

Command::Command(string com, string eff)
{ // parametrized constructor
    this->command = com;
    this->effect = eff;
}

Command::Command(const Command &c)
{ // copy constructor
    this->command = c.command;
    this->effect = c.effect;
}

Command::~Command()
{ // destructor
}

void Command::saveEffect(string eff)
{
    this->effect = eff;
}

