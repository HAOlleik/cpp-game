#include "GameEngine.h"

void inputToLower(char *input) // switches passed arguments to lower case
{
    int inputCharCounter = 0;
    char inputChar;
    while (input[inputCharCounter])
    {
        inputChar = input[inputCharCounter];
        input[inputCharCounter] = tolower(inputChar);
        inputCharCounter++;
    }
}

GameEngine::GameEngine()
{ // default constructor
    state = new State(start);
}

GameEngine::GameEngine(const GameEngine &g)
{ // copy constructor
    (*this).state = g.state;
}

GameEngine::~GameEngine()
{ // destructor
    std::cout << "Game engine destroyed\n";
}

// assignment operator overload
GameEngine &GameEngine::operator=(const GameEngine &g)
{
    (*this).state = g.state;
    return *this;
}

ostream &operator<<(ostream &os, GameEngine &gameEngine)
{ // insert stream operator
    const char *currentStateString;
    // getCommand(currentStaet:state) -> process
    // if effect is not empty then it is an error
    switch (*(gameEngine.getState()))
    {
    case 1:
        currentStateString = "Start";
        // 4) use the gamestart command to
        // a) fairly distribute all the territories to the players
        // b) determine randomly the order of play of the players in the game
        // c) give 50 initial army units to the players, which are placed in their respective reinforcement pool
        // d) let each player draw 2 initial cards from the deck using the deck’s draw() method
        // e) switch the game to the play phase
        break;
    case 2:
        // 1) use the loadmap <filename> command to select a map from a list of map files as stored in a directory,
        // which results in the map being loaded in the game.

        currentStateString = "Map Loaded";
        break;
    case 3:
        currentStateString = "Map Validated";
        // 2) use the validatemap command to validate the map (i.e. it is a connected graph, etc – see assignment 1).
        break;
    case 4:
        currentStateString = "Players Added";
        // 3) use the addplayer <playername> command to enter players in the game (2-6 players)
        break;
    case 5:
        currentStateString = "Assign Reinforcement";
        break;
    case 6:
        currentStateString = "Issue Orders";
        break;
    case 7:
        currentStateString = "Execute Orders";
        break;
    case 8:
        currentStateString = "Win";
        break;
    default:
        break;
    }

    // command->saveEffect(newState or error: string);

    os << "The current state is: " << currentStateString << "\n\n";
    return os;
}
