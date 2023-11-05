#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <memory>
#include <map>
using std::ostream;

#include "Player.h"
#include "Map.h"

enum State // available states
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

enum Action // available actions
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

std::map<State, std::map<Action, State>> mapStateToActions{// map of possible actions from a state, and the leading state of that action
                                                           {start, {{load_map, map_loaded}}},
                                                           {map_loaded, {{load_map, map_loaded}, {validate_map, map_validated}}},
                                                           {map_validated, {{add_player, players_added}}},
                                                           {players_added, {{add_player, players_added}, {assign_countries, assign_reinforcement}}},
                                                           {assign_reinforcement, {{issue_order, issue_orders}}},
                                                           {issue_orders, {{issue_order, issue_orders}, {end_issue_orders, execute_orders}}},
                                                           {execute_orders, {{exec_order, execute_orders}, {end_exec_orders, assign_reinforcement}, {win_game, win}}},
                                                           {win, {{play, start}}}};

std::map<std::string, Action> actionToString{// map between string and action to be able to compare values
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

void inputToLower(char *input); // free function to change to inputted action to lower case

class GameEngine
{
public:
    GameEngine();                                         // default
    GameEngine(const GameEngine &g);                      // copy constr
    GameEngine &operator=(const GameEngine &c);           // assignment operator overload
    ~GameEngine();                                        // destructor
    State *getState() { return state; };                  // getter for state
    void setState(State *newState) { state = newState; }; // setter for state
    void startupPhase();                                  // TBD

private:
    State *state;
    std::vector<shared_ptr<Player>> _player;
    std::unique_ptr<Map> _map;
};

ostream &
operator<<(ostream &os, GameEngine &g);
void testGameEngineStates();
#endif