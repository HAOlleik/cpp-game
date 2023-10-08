#include "GameEngine.h"

void inputToLower(char* input) // switches passed arguments to lower case
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

GameEngine::GameEngine() { // default constructor
    state = new State(start);
}

GameEngine::GameEngine(const GameEngine &g) { // copy constructor
    (*this).state = g.state;
}

GameEngine::~GameEngine() { // destructor
    std::cout << "Game engine destroyed\n";
    delete state;
}

std::map<State, std::map<Action, State>> mapStateToActions{ // map of possible actions from a state, and the leading state of that action
    {start, {{load_map, map_loaded}}},
    {map_loaded, {{load_map, map_loaded}, {validate_map, map_validated}}},
    {map_validated, {{add_player, players_added}}},
    {players_added, {{add_player, players_added}, {assign_countries, assign_reinforcement}}},
    {assign_reinforcement, {{issue_order, issue_orders}}},
    {issue_orders, {{issue_order, issue_orders}, {end_issue_orders, execute_orders}}},
    {execute_orders, {{exec_order, execute_orders}, {end_exec_orders, assign_reinforcement}, {win_game, win}}},
    {win, {{play, start}}}};

std::map<std::string, Action> actionToString{ // map between string and action to be able to compare values
    {"loadmap", load_map},
    {"validatemap", validate_map},
    {"addplayer", add_player},
    {"assigncountries", assign_countries},
    {"issueorder", issue_order},
    {"endissueorders", end_issue_orders},
    {"execorder", exec_order},
    {"endexecorders", end_exec_orders},
    {"win", win_game},
    {"play", play},
    {"end", end_game}};


//assignment operator overload
GameEngine &GameEngine::operator = (const GameEngine &g)
{
    (*this).state = g.state;
    return *this;
}

ostream& operator<<(ostream& os, GameEngine& gameEngine) { //insert stream operator
    const char* currentStateString = nullptr; // Initialize to nullptr

    switch (*(gameEngine.getState())) {
        case 1:
            currentStateString = "Start";
            break;
        case 2:
            currentStateString = "Map Loaded";
            break;
        case 3:
            currentStateString = "Map Validated";
            break;
        case 4:
            currentStateString = "Players Added";
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

    os << "The current state is: " << currentStateString << "\n";
    return os;
}
