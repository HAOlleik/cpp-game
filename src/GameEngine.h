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
    map_loaded,
    map_validated,
    players_added,
    assign_reinforcement,
    issue_orders,
    execute_orders,
    win,
    game_ended
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
    {"game_ended", STATE::game_ended},
};

// available actions
enum ACTION
{
    load_map = 1,
    validate_map,
    add_player,
    gamestart,
    assign_countries,
    issue_order,
    end_issue_orders,
    exec_order,
    end_exec_orders,
    win_game,
    end_game,
    replay
};

// transform string to action enum, kind hack
std::map<std::string, ACTION> actionMap = {
    {"load_map", ACTION::load_map},
    {"validate_map", ACTION::validate_map},
    {"add_player", ACTION::add_player},
    {"gamestart", ACTION::gamestart},
    {"assign_countries", ACTION::assign_countries},
    {"issue_order", ACTION::issue_order},
    {"end_issue_orders", ACTION::end_issue_orders},
    {"exec_order", ACTION::exec_order},
    {"end_exec_orders", ACTION::end_exec_orders},
    {"win_game", ACTION::win_game},
    {"end_game", ACTION::end_game},
    {"replay", ACTION::replay},
};

// map of possible actions from a state, and the leading state of that action
std::map<STATE, std::map<ACTION, STATE>> mapStateToActions{
    {STATE::start, {{ACTION::load_map, STATE::map_loaded}}},
    {STATE::map_loaded, {{ACTION::load_map, STATE::map_loaded}, {ACTION::validate_map, STATE::map_validated}}},
    {STATE::map_validated, {{ACTION::add_player, STATE::players_added}}},
    {STATE::players_added, {{ACTION::add_player, STATE::players_added}, {ACTION::gamestart, STATE::assign_reinforcement}}},
    {STATE::assign_reinforcement, {{ACTION::issue_order, STATE::issue_orders}}},
    {STATE::issue_orders, {{ACTION::issue_order, STATE::issue_orders}, {ACTION::end_issue_orders, STATE::execute_orders}}},
    {STATE::execute_orders, {{ACTION::exec_order, STATE::execute_orders}, {ACTION::end_exec_orders, STATE::assign_reinforcement}, {ACTION::win_game, STATE::win}}},
    {STATE::win, {{ACTION::end_game, STATE::game_ended}, {ACTION::replay, STATE::start}}}};

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
    void startupPhase();
    ACTION playPhase();
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
