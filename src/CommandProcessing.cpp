#include "CommandProcessing.h"
#include "GameEngine.h"

CommandProcessor::CommandProcessor(const CommandProcessor &cp)
{ // copy constructor
    for (const Command &cmd : cp.savedCommands)
    {
        savedCommands.push_back(cmd);
    }
}

CommandProcessor::~CommandProcessor()
{ // destructor
    std::cout << "Command Processor destroyed\n";
}

void CommandProcessor::readCommand(char *command)
{
    cout << "Please insert next command\n";
    cin >> command;
}

Command CommandProcessor::saveCommand(char *command, char *effect)
{
    inputToLower(command);
    Command commandObj(command, effect);
    savedCommands.push_back(commandObj);
    return commandObj;
}

void CommandProcessor::validate(State currentState, string checkedCommand, char* effect)
{
    if (actionToString[checkedCommand] != 0 && mapStateToActions[currentState][actionToString[checkedCommand.getCommand()]] != 0)
    {
        effect = "";
    }
    else
    {
        effect = "Error! Command is incompatible for current state";
    }
}

Command CommandProcessor::getCommand(State currentState)
{
    char *command;
    char *effect;
    readCommand(command);
    validate(currentState, command, effect);
    return saveCommand(command, effect);
}

// **************************************** Command ***************************/
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
    std::cout << "Command destroyed\n";
}

void Command::saveEffect(string eff)
{
    effect = eff;
}

FileLineReader &FileLineReader::operator=(const FileLineReader &cp)
{
    if (this != &cp) // Check for self-assignment
    {
        filename = cp.filename;
        fileStream.close();
        fileStream.open(filename);
    }
    return *this;
}

FileLineReader::~FileLineReader()
{ // destructor
    if (fileStream.is_open())
    {
        fileStream.close();
    }
}

std::string FileLineReader::readLineFromFile()
{
    std::string line;
    getline(fileStream, line);
    return line;
}

void FileCommandProcessorAdapter::readCommand(char *command)
{
    std::string line = fileLineReader.readLineFromFile();
    if (!line.empty())
    {
        strncpy(command, line.c_str(), std::min(maxCommandLength - 1, line.length()));
    }
    else
    {
        command[0] = '\0'; // Empty command
    }
}

FileCommandProcessorAdapter &FileCommandProcessorAdapter::operator=(const FileCommandProcessorAdapter &cp)
{
        if (this != &cp)
        {
            fileLineReader = cp.fileLineReader;
        }
        return *this;
    }
