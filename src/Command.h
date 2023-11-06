#ifndef COMMAND_H
#define COMMAND_H

#include <string.h>
#include <iostream>

using namespace std;

class Command
{
private:
    string *command;
    string *effect;

public:
    Command();                            // default
    Command(string& com, string& eff);      // parametrized constr
    Command(const Command &c);            // copy constr
    Command &operator=(const Command &c); // assignment operator overload
    ~Command();                           // destructor
    void saveEffect(string eff);
    string getCommand() { return *command; };
    string getEffect() { return *effect; };
    void setCommand(string& newCommand) { *command = newCommand; };
    void setEffect(string& newEffect) { *effect = newEffect; };
    friend ostream &operator<<(ostream &os, Command &c);
};


#endif
