#include "GameEngine.h"

void inputToLower(char* input)
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

GameEngine::GameEngine() {
    state = start;
}

GameEngine::GameEngine(const GameEngine &g) {
    (*this).state = g.state;
}

GameEngine::~GameEngine() {
    std::cout << "Game engine destroyed\n";
}

std::map<State, std::map<Action, State>> mapStateToActions{
    {start, {{load_map, map_loaded}}},
    {map_loaded, {{load_map, map_loaded}, {validate_map, map_validated}}},
    {map_validated, {{add_player, players_added}}},
    {players_added, {{add_player, players_added}, {assign_countries, assign_reinforcement}}},
    {assign_reinforcement, {{issue_order, issue_orders}}},
    {issue_orders, {{issue_order, issue_orders}, {end_issue_orders, execute_orders}}},
    {execute_orders, {{exec_order, execute_orders}, {end_exec_orders, assign_reinforcement}, {win_game, win}}},
    {win, {{play, start}}}};

std::map<std::string, Action> actionToString{
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
