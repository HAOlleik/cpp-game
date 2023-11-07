#include "CommandProcessing.h"

bool isFileAvailable(const std::string &filePath)
{
    std::ifstream file(filePath.c_str());
    return file.good();
}

string strToLower(string str) {
    string upperStr = str;
    for (char& c : upperStr) {
        c = std::tolower(c);
    }
    return upperStr;
}

CommandProcessor::CommandProcessor(const CommandProcessor &cp)
{ // copy constructor
    for (const Command &cmd : *(cp.savedCommands))
    {
        savedCommands->push_back(cmd);
    }
}

CommandProcessor::~CommandProcessor()
{
    delete savedCommands;
}

void CommandProcessor::readCommand(string& command)
{
    cout << "Please insert next command\n";
    getline(cin, command);
}

Command CommandProcessor::saveCommand(string command, string effect)
{
    Command commandObj(command, effect);
    savedCommands->push_back(commandObj);
    return commandObj;
}

void CommandProcessor::validate(STATE currentState, string checkedCommand, string &effect)
{
    size_t spacePos = checkedCommand.find(' ');
    string firstPart = "";
    string secondPart = "";
    effect = "";
    if (spacePos != string::npos)
    {
        firstPart = checkedCommand.substr(0, spacePos);
        secondPart = checkedCommand.substr(spacePos + 1);
    } else {
        firstPart = checkedCommand;
    }

    firstPart = strToLower(firstPart);
    checkedCommand = firstPart + " " + secondPart;
    if (actionMap[firstPart] == 0 || mapStateToActions[currentState][actionMap[firstPart]] == 0)
    {
        effect = "error because command is incompatible for current state.";
    }
    else if (!isFileAvailable(secondPart) && secondPart != "")
    {
        effect = "error because file is not available!";
    }
}

Command CommandProcessor::getCommand(STATE currentState)
{
    string command;
    string effect;
    readCommand(command);
    validate(currentState, command, effect);
    return saveCommand(command, effect);
}


FileLineReader::FileLineReader(const string &filename) {
    this->filename = new string(filename);;
    fileStream = new ifstream(*this->filename);
    if (!fileStream->is_open()) {
        cerr << "Error: Could not open file " << *this->filename << endl;
        exit(1);
    }
}

FileLineReader::FileLineReader(const FileLineReader &cp)
{
    this->filename = new std::string(*cp.filename);
    this->fileStream = new std::ifstream(*filename);
    if (!fileStream->is_open()) {
        cerr << "Error: Could not open file " << *filename << endl;
    }
}

FileLineReader &FileLineReader::operator=(const FileLineReader &cp)
{
    if (this != &cp) {
        // Release existing resources
        delete filename;
        if (fileStream->is_open()) {
            fileStream->close();
        }
        
        // Allocate new memory
        this->filename = new string(*(cp.filename));
        fileStream = new ifstream(*this->filename);
        if (!fileStream->is_open()) {
            cerr << "Error: Could not open file " << *this->filename << endl;
        }
    }
    return *this;
}

FileLineReader::~FileLineReader()
{
    delete filename;
    if (fileStream->is_open())
    {
        fileStream->close();
    }
}

std::string FileLineReader::readLineFromFile()
{
    std::string line;
    getline(*fileStream, line);
    return line;
}


FileCommandProcessorAdapter::FileCommandProcessorAdapter(string fileName)
{ // parametrized constructor
    fileLineReader = new FileLineReader(fileName);
}

void FileCommandProcessorAdapter::readCommand(string& command)
{
    std::string line = fileLineReader->readLineFromFile();
    if (!line.empty())
    {
        command = line;
    }
    else
    {
        command.clear();  // Empty command
    }
}

FileCommandProcessorAdapter &FileCommandProcessorAdapter::operator=(const FileCommandProcessorAdapter &cp)
{
    if (this != &cp)
    {
        delete fileLineReader;
        fileLineReader = cp.fileLineReader;
    }
    return *this;
}

ostream& operator<<(ostream& os, Command& c) {
    os << "The command is " << c.getCommand() << " and the effect is " << c.getEffect() << "\n";
    return os;
}

ostream& operator<<(ostream& os, CommandProcessor& cp) {
    int counter = 1;
    os << "The list of commands now are: \n";
    for (Command& command : *(cp.savedCommands)) {
        os << counter << "- " << command;
        counter++;
    }
    return os;
}

ostream& operator<<(ostream& os, FileLineReader& flr) {
    os << "working on file " << *flr.filename << "\n";
    return os;
}

ostream& operator<<(ostream& os, FileCommandProcessorAdapter& fcpa) {
    int counter = 1;
    os << "My reader is " << *fcpa.fileLineReader << "\n";
    os << "The list of commands now are: \n";
    for (Command& command : fcpa.getSavedCommands()) {
        os << counter << "- " << command;
        counter++;
    }
    return os;
}
