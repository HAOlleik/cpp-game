#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <tuple>
#include <string>
#include <string.h>
#include <iostream>
#include "LoggingObserver.h"

using namespace std;

class Command : public ILoggable, public Subject
{
private:
    string *command;
    string *effect;
    std::tuple<std::vector<std::string>, std::vector<std::string>, int, int> tournamentParameters;

public:
    Command();                            // default
    Command(string &com, string &eff);    // parametrized constr
    Command(const Command &c);            // copy constr
    Command &operator=(const Command &c); // assignment operator overload
    ~Command();                           // destructor
    void saveEffect(string eff);
    string stringToLog();
    string getCommand() { return *command; };
    string getEffect() { return *effect; };
    void setCommand(string &newCommand) { *command = newCommand; };
    void setEffect(string &newEffect) { *effect = newEffect; };
    friend ostream &operator<<(ostream &os, Command &c);
    std::tuple<std::vector<std::string>, std::vector<std::string>, int, int> getTournamentParameters() const;
};

#endif
