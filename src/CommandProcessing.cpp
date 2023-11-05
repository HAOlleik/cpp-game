#include <fstream>

#include "CommandProcessing.h"
#include "GameEngine.h"

bool isFileAvailable(const std::string &filePath)
{
    std::ifstream file(filePath.c_str());
    return file.good();
}

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
    Command commandObj(command, effect);
    savedCommands.push_back(commandObj);
    return commandObj;
}

void CommandProcessor::validate(State currentState, string checkedCommand, char *effect)
{
    size_t spacePos = checkedCommand.find(' ');
    string firstPart = "";
    string secondPart = "";
    effect = "";
    if (spacePos != string::npos)
    {
        firstPart = checkedCommand.substr(0, spacePos);
        secondPart = checkedCommand.substr(spacePos + 1);
    }
    stringToLower(firstPart);
    checkedCommand = firstPart + " " + secondPart;

    if (actionToString[firstPart] == 0 && mapStateToActions[currentState][actionToString[firstPart]] == 0)
    {
        effect = "Error! Command is incompatible for current state";
    }
    else if (!isFileAvailable(secondPart))
    {
        effect = "File is not available!";
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
        strcpy(command, line.c_str());
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

ostream& operator<<(ostream& os, Command& c) {
    os << "The command is " << c.getCommand() << " and the effect is " << c.getEffect() << "\n\n";
    return os;
}

ostream& operator<<(ostream& os, CommandProcessor& cp) {
    int counter = 1;
    os << "The list of commands now are: \n";
    for (const Command& command : cp.savedCommands) {
        os << counter << "- " << &command << "\n\n";
        counter++;
    }
    return os;
}
