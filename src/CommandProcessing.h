#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H
#include <iostream>
#include <string.h>
#include <fstream>
#include <list>
#include "GameEngine.h"
using namespace std;

class Command
{
private:
    string command;
    string effect;

public:
    Command();                            // default
    Command(string com, string eff);      // parametrized constr
    Command(const Command &c);            // copy constr
    Command &operator=(const Command &c); // assignment operator overload
    ~Command();                           // destructor
    void saveEffect(string eff);
    string getCommand() { return this->command; };
    string getEffect() { return effect; };
    void setCommand(string newCommand) { command = newCommand; };
    void setEffect(string newEffect) { effect = newEffect; };
};

class CommandProcessor
{
private:
    list<Command> savedCommands;
    virtual void readCommand(char *command);
    Command saveCommand(char *command);
    bool validate(State currentState, string checkedCommand);

public:
    CommandProcessor() : savedCommands(){};                  // default
    CommandProcessor(const CommandProcessor &cp);            // copy constr
    CommandProcessor &operator=(const CommandProcessor &cp); // assignment operator overload
    ~CommandProcessor();                                     // destructor
    Command getCommand(State currentState);
};

class FileLineReader
{
private:
    string filename;
    ifstream fileStream;

public:
    FileLineReader() : filename(""), fileStream() {}
    FileLineReader(const std::string& filename) : filename(filename), fileStream(filename) {}
    FileLineReader(const FileLineReader &cp) : filename(cp.filename), fileStream(cp.filename){}
    FileLineReader &operator=(const FileLineReader &cp); // assignment operator overload
    ~FileLineReader();                                   // destructor
    string readLineFromFile();
};

class FileCommandProcessorAdapter : public CommandProcessor
{
private:
    FileLineReader fileLineReader;
    void readCommand(char *command) override;

public:
    FileCommandProcessorAdapter();                                                 // default
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter &cp);            // copy constr
    FileCommandProcessorAdapter &operator=(const FileCommandProcessorAdapter &cp); // assignment operator overload
    ~FileCommandProcessorAdapter();
};

void testCommandProcessor();
#endif