#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <map>
using std::ostream;

enum State
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

enum Action
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

extern std::map<State, std::map<Action, State>> mapStateToActions;
extern std::map<std::string, Action> actionToString;

void inputToLower(char* input);

class GameEngine
{
private:
    State state;

public:
    GameEngine();
    GameEngine(const GameEngine &g);
    ~GameEngine();
    State getState() { return state; };
    void setState(State &newState) { state = newState; };
};

ostream &
operator<<(ostream &os, GameEngine &g);

#endif