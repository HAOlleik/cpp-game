#include "Command.h"

Command::Command()
{ // default constructor
    this->command = nullptr;
    this->effect = nullptr;
}

Command::Command(string &com, string &eff)
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

// Assignment operator
Command &Command::operator=(const Command &other)
{
    if (this != &other)
    {
        // Delete existing resources
        delete command;
        delete effect;

        // Copy new resources
        command = new std::string(*(other.command));
        effect = new std::string(*(other.effect));
    }
    return *this;
}

void Command::saveEffect(string eff)
{
    if (effect)
    {
        *effect = eff; // Update the existing string
    }
    else
    {
        effect = new string(eff); // If effect is nullptr, create a new string
    }
    notify(this);
}

string Command::stringToLog()
{
    string returnString = "The command's effect is: " + getEffect();
    return returnString;
}

std::tuple<std::vector<std::string>, std::vector<std::string>, int, int> Command::getTournamentParameters() const
{
    // Return the stored tournament parameters
    return tournamentParameters;
}