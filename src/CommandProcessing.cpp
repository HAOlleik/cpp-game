#include "CommandProcessing.h"

bool isFileAvailable(const std::string &filePath)
{
    std::ifstream file(filePath.c_str());
    return file.good();
}

string strToLower(string str)
{
    string upperStr = str;
    for (char &c : upperStr)
    {
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

void CommandProcessor::readCommand(string &command)
{
    cout << "Please insert next command\n";
    getline(cin, command);
}

Command CommandProcessor::saveCommand(string command, string effect)
{
    Command commandObj(command, effect);
    savedCommands->push_back(commandObj);
    notify(this);
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
    }
    else
    {
        firstPart = checkedCommand;
    }

    firstPart = strToLower(firstPart);
    checkedCommand = firstPart + " " + secondPart;
    std::cout << "current state now is  " << currentState << std::endl;
    if (actionMap[firstPart] == 0 || mapStateToActions[currentState][actionMap[firstPart]] == 0)
    {
        effect = "error because command is incompatible for current state.";
    }
    // else if (!isFileAvailable(secondPart) && secondPart != "")
    // {
    //     effect = "error because file is not available!";
    // }
}

Command CommandProcessor::getCommand(STATE currentState)
{
    string command;
    string effect;
    readCommand(command);
    validate(currentState, command, effect);
    return saveCommand(command, effect);
}

string CommandProcessor::stringToLog()
{
    string returnString = "The command has been saved with an effect of: ";

    if (savedCommands != nullptr && !savedCommands->empty())
    {
        Command lastCommand = savedCommands->back();    // Get the last command in the list
        string commandEffect = lastCommand.getEffect(); // Get the effect of the last command

        return returnString + commandEffect;
    }

    return returnString + "Unknown";
}

FileLineReader::FileLineReader(const string &filename)
{
    this->filename = new string(filename);
    ;
    fileStream = new ifstream(*this->filename);
    if (!fileStream->is_open())
    {
        cerr << "Error: Could not open file " << *this->filename << endl;
        exit(1);
    }
}

FileLineReader::FileLineReader(const FileLineReader &cp)
{
    this->filename = new std::string(*cp.filename);
    this->fileStream = new std::ifstream(*filename);
    if (!fileStream->is_open())
    {
        cerr << "Error: Could not open file " << *filename << endl;
    }
}

FileLineReader &FileLineReader::operator=(const FileLineReader &cp)
{
    if (this != &cp)
    {
        // Release existing resources
        delete filename;
        if (fileStream->is_open())
        {
            fileStream->close();
        }

        // Allocate new memory
        this->filename = new string(*(cp.filename));
        fileStream = new ifstream(*this->filename);
        if (!fileStream->is_open())
        {
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

void FileCommandProcessorAdapter::readCommand(string &command)
{
    std::string line = fileLineReader->readLineFromFile();
    if (!line.empty())
    {
        command = line;
    }
    else
    {
        command.clear(); // Empty command
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

ostream &operator<<(ostream &os, Command &c)
{
    os << "The command is " << c.getCommand() << " and the effect is " << c.getEffect() << "\n";
    return os;
}

ostream &operator<<(ostream &os, CommandProcessor &cp)
{
    int counter = 1;
    os << "The list of commands now are: \n";
    for (Command &command : *(cp.savedCommands))
    {
        os << counter << "- " << command;
        counter++;
    }
    return os;
}

ostream &operator<<(ostream &os, FileLineReader &flr)
{
    os << "working on file " << *flr.filename << "\n";
    return os;
}

ostream &operator<<(ostream &os, FileCommandProcessorAdapter &fcpa)
{
    int counter = 1;
    os << "My reader is " << *fcpa.fileLineReader << "\n";
    os << "The list of commands now are: \n";
    for (Command &command : fcpa.getSavedCommands())
    {
        os << counter << "- " << command;
        counter++;
    }
    return os;
}

#include <sstream>

Command CommandProcessor::processTournamentCommand(STATE currentState)
{
    string command;
    string effect;
    readCommand(command);
    validate(currentState, command, effect);

    // Handle validation error
    if (!effect.empty())
    {
        return saveCommand(command, effect);
    }

    std::vector<std::string> tokens = splitCommand(command);

    // Validate the number of tokens
    if (tokens.size() < 9 || tokens.size() % 2 != 1)
    {
        std::cerr << "Error: Invalid number of parameters for the tournament command." << std::endl;
        // Set an error message in the Command object
        return saveCommand(command, "Invalid number of parameters for the tournament command.");
    }

    // Validate the command format
    if (tokens[0] != "tournament" || tokens[2] != "-M" || tokens[4] != "-P" || tokens[6] != "-G" || tokens[8] != "-D")
    {
        std::cerr << "Error: Invalid format for the tournament command." << std::endl;
        // Set an error message in the Command object
        return saveCommand(command, "Invalid format for the tournament command.");
    }

    // Extract and store tournament parameters
    std::vector<std::string> mapFiles;
    std::vector<std::string> playerStrategies;
    int numGames = 0;
    int maxTurns = 0;

    for (size_t i = 3; i < tokens.size(); i += 2)
    {
        if (tokens[i] == "-M")
        {
            mapFiles.push_back(tokens[i + 1]);
        }
        else if (tokens[i] == "-P")
        {
            playerStrategies.push_back(tokens[i + 1]);
        }
        else if (tokens[i] == "-G")
        {
            numGames = std::stoi(tokens[i + 1]);
        }
        else if (tokens[i] == "-D")
        {
            maxTurns = std::stoi(tokens[i + 1]);
        }
    }

    // Check if the parameters are within the specified range
    if (mapFiles.size() < 1 || mapFiles.size() > 5 ||
        playerStrategies.size() < 2 || playerStrategies.size() > 4 ||
        numGames < 1 || numGames > 5 ||
        maxTurns < 10 || maxTurns > 50)
    {
        std::cerr << "Error: Invalid parameter values for the tournament command." << std::endl;
        // Set an error message in the Command object
        return saveCommand(command, "Invalid parameter values for the tournament command.");
    }

    // Store the tournament parameters
    tournamentParameters = std::make_tuple(mapFiles, playerStrategies, numGames, maxTurns);

    // Set a success message in the Command object
    return saveCommand(command, "Tournament parameters processed successfully.");
}

#include <vector>
#include <string>
#include <sstream>
#include <iterator>

std::vector<std::string> CommandProcessor::splitCommand(const std::string &command)
{
    std::vector<std::string> tokens;
    std::istringstream iss(command);
    std::string token;

    while (std::getline(iss, token, ' '))
    {
        if (!token.empty())
        {
            // Remove surrounding quotation marks if present
            if (token.front() == '"' && token.back() == '"')
            {
                token = token.substr(1, token.size() - 2);
            }
            tokens.push_back(token);
        }
    }

    return tokens;
}

std::tuple<std::vector<std::string>, std::vector<std::string>, int, int> CommandProcessor::getTournamentParameters() const
{
    // Return the stored tournament parameters
    return tournamentParameters;
}
