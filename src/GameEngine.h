#ifndef CARD_H
#define CARD_H
#include <iostream>
using std::ostream;
#include <bits/stdc++.h>
#include <memory>
#include <map>

#include "Player.h"
#include "Map.h"
#include "CommandProcessing.h"
#include "MapLoader.h"

#define MAX_PLAYERS = 6

// available states
enum STATE
{
    start = 1,
    map_loaded = 2,
    map_validated = 3,
    players_added = 4,
    assign_reinforcement = 5,
    issue_orders = 6,
    execute_orders = 7,
    win = 8
};

// transform string to state enum, kind hack
static std::map<std::string, STATE> stateMap = {
    {"start", STATE::start},
    {"map_loaded", STATE::map_loaded},
    {"map_validated", STATE::map_validated},
    {"players_added", STATE::players_added},
    {"assign_reinforcement", STATE::assign_reinforcement},
    {"issue_orders", STATE::issue_orders},
    {"execute_orders", STATE::execute_orders},
    {"win", STATE::win},
};

// available actions
enum ACTION
{
    load_map = 1,
    validate_map = 2,
    add_player = 3,
    assign_countries = 4,
    issue_order = 5,
    end_issue_orders = 6,
    exec_order = 7,
    end_exec_orders = 8,
    win_game = 9,
    play = 10,
    end_game = 11
};

// transform string to action enum, kind hack
std::map<std::string, ACTION> actionMap = {
    {"load_map", ACTION::load_map},
    {"validate_map", ACTION::validate_map},
    {"add_player", ACTION::add_player},
    {"assign_countries", ACTION::assign_countries},
    {"issue_order", ACTION::issue_order},
    {"end_issue_orders", ACTION::end_issue_orders},
    {"exec_order", ACTION::exec_order},
    {"end_exec_orders", ACTION::end_exec_orders},
    {"win_game", ACTION::win_game},
    {"play", ACTION::play},
    {"end_game", ACTION::end_game},
};

// map of possible actions from a state, and the leading state of that action
std::map<STATE, std::map<ACTION, STATE>> mapStateToActions{
    {start, {{load_map, map_loaded}}},
    {map_loaded, {{load_map, map_loaded}, {validate_map, map_validated}}},
    {map_validated, {{add_player, players_added}}},
    {players_added, {{add_player, players_added}, {assign_countries, assign_reinforcement}}},
    {assign_reinforcement, {{issue_order, issue_orders}}},
    {issue_orders, {{issue_order, issue_orders}, {end_issue_orders, execute_orders}}},
    {execute_orders, {{exec_order, execute_orders}, {end_exec_orders, assign_reinforcement}, {win_game, win}}},
    {win, {{play, start}}}};

// map between string and action to be able to compare values
std::map<std::string, ACTION> actionToString{
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

// free function to change to inputted action to lower case
void inputToLower(char *input);

class GameEngine
{
public:
    GameEngine();                               // default
    GameEngine(const GameEngine &g);            // copy constr
    GameEngine(CommandProcessor cli);           // paratemtrized contructor
    GameEngine &operator=(const GameEngine &c); // assignment operator
    ~GameEngine();                              // destructor
    void startupPhase();                        // TBD

    STATE *getState() const // getter for state
    {
        return _state.get();
    };
    void setState(STATE *newState) // setter for state
    {
        _state = std::make_shared<STATE>(*newState);
    };

private:
    std::shared_ptr<STATE> _state = NULL;
    std::vector<shared_ptr<Player>> _players;
    std::unique_ptr<Map> _map = NULL;
    std::unique_ptr<CommandProcessor> cli = NULL;
};

ostream &operator<<(ostream &os, GameEngine &g);
void testGameEngineStates();

// switches passed arguments to lower case
void inputToLower(char *input)
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
#endif
