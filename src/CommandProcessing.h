#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H
#include <iostream>
#include <string.h>
#include <fstream>
#include <list>
using namespace std;

class Command
{
private:
    string command;
    string effect;

public:
    Command();                                         // default
    Command(const Command &c);                      // copy constr
    Command &operator=(const Command &c);           // assignment operator overload
    ~Command();                                        // destructor
    void saveEffect();
};

class CommandProcessor
{
private:
    list<Command> savedCommands;
    virtual void readCommand();
    void saveCommand();
    bool validate();

public:
    CommandProcessor();                                         // default
    CommandProcessor(const CommandProcessor &cp);                      // copy constr
    CommandProcessor &operator=(const CommandProcessor &cp);           // assignment operator overload
    ~CommandProcessor();                                        // destructor
    Command getCommand();
};

class FileLineReader
{
private:
    string filename;
    ifstream fileStream;
public:
    FileLineReader();                                         // default
    FileLineReader(const FileLineReader &cp);                      // copy constr
    FileLineReader &operator=(const FileLineReader &cp);           // assignment operator overload
    ~FileLineReader();                                        // destructor
    string readLineFromFile();
};

class FileCommandProcessorAdapter : public CommandProcessor
{
private:
    FileLineReader fileLineReader;
    void readCommand() override;

public:
    FileCommandProcessorAdapter();                                         // default
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter &cp);                      // copy constr
    FileCommandProcessorAdapter &operator=(const FileCommandProcessorAdapter &cp);           // assignment operator overload
    ~FileCommandProcessorAdapter();
};

void testCommandProcessor();
#endif