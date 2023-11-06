#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H
#include <iostream>
#include <string.h>
#include <fstream>
#include <list>
#include "Command.h"
#include "GameEngineState.h"
using namespace std;

string strToLower(string str);

class CommandProcessor
{
private:
    list<Command> *savedCommands;
    virtual void readCommand(string &command);
    Command saveCommand(string command, string effect);
    void validate(STATE currentState, string checkedCommand, string &effect);

protected:
    list<Command>& getSavedCommands() const {
        return *savedCommands;
    }

public:
    CommandProcessor() : savedCommands(new list<Command>()){};                  // default
    CommandProcessor(const CommandProcessor &cp);            // copy constr
    CommandProcessor &operator=(const CommandProcessor &cp); // assignment operator overload
    ~CommandProcessor();                                     // destructor
    Command getCommand(STATE currentState);
    friend ostream &operator<<(ostream &os, CommandProcessor &cp);
};

class FileLineReader
{
private:
    string *filename;
    ifstream *fileStream;

public:
    FileLineReader() : filename(nullptr), fileStream(nullptr) {}
    FileLineReader(const string &filename);
    FileLineReader(const FileLineReader &cp);
    FileLineReader &operator=(const FileLineReader &cp); // assignment operator overload
    ~FileLineReader();                                   // destructor
    string readLineFromFile();
    friend ostream &operator<<(ostream &os, FileLineReader &flr);
};

class FileCommandProcessorAdapter : public CommandProcessor
{
private:
    FileLineReader *fileLineReader;
    void readCommand(string &command) override;

public:
    FileCommandProcessorAdapter() : fileLineReader(nullptr) {}                                                       // default
    FileCommandProcessorAdapter(string fileName);                                                      // default
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter &cp) : CommandProcessor(cp), fileLineReader(cp.fileLineReader) {} // copy constr
    FileCommandProcessorAdapter &operator=(const FileCommandProcessorAdapter &cp);                            // assignment operator overload
    ~FileCommandProcessorAdapter() {delete fileLineReader;}
    friend ostream &operator<<(ostream &os, FileCommandProcessorAdapter &fcpa);
};

ostream &operator<<(ostream &os, Command &c);
ostream &operator<<(ostream &os, CommandProcessor &cp);
ostream &operator<<(ostream &os, FileLineReader &flr);
ostream &operator<<(ostream &os, FileCommandProcessorAdapter &fcpa);

#endif
