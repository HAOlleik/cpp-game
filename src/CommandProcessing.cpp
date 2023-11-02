#include "CommandProcessing.h"
#include "GameEngine.h"

CommandProcessor::CommandProcessor(const CommandProcessor &cp) { // copy constructor
    for (const Command &cmd : cp.savedCommands) {
            savedCommands.push_back(cmd);
    }
}

CommandProcessor::~CommandProcessor() { // destructor
    std::cout << "Command Processor destroyed\n";
}

void CommandProcessor::readCommand(char* command) {
    cout << "Please insert next command\n";
    cin >> command;
}

void CommandProcessor::saveCommand(char* command) {
    inputToLower(command);
    Command commandObj(command, "");
    savedCommands.push_back(commandObj);
}

bool CommandProcessor::validate(State currentState, Command checkedCommand) {
    if(actionToString[checkedCommand.getCommand()] != 0 && mapStateToActions[currentState][actionToString[checkedCommand.getCommand()]] != 0) {
        return true;
    } else {
        return false;
    }
}

void CommandProcessor::getCommand() {
    char* command;
    readCommand(command);
    
}


Command::Command() { // default constructor
    command = "";
    effect = "";
}

Command::Command(string com, string eff) { // parametrized constructor
    command = com;
    effect = eff;
}

Command::Command(const Command &c) { // copy constructor
    (*this).command = c.command;
    (*this).effect = c.effect;
}

Command::~Command() { // destructor
    std::cout << "Command destroyed\n";
}

void Command::saveEffect(string eff) {
    effect = eff;
}

FileLineReader::FileLineReader() { // default constructor
    state = new State(start);
}

FileLineReader::FileLineReader(const FileLineReader &g) { // copy constructor
    (*this).state = g.state;
}

FileLineReader::~FileLineReader() { // destructor
    std::cout << "Game engine destroyed\n";
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter() { // default constructor
    state = new State(start);
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter &g) { // copy constructor
    (*this).state = g.state;
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter() { // destructor
    std::cout << "Game engine destroyed\n";
}