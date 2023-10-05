#ifndef CARD_H
#define CARD_H
#include <iostream>
using std::ostream;

enum State
{
    start,
    map_loaded,
    map_validated,
    players_added,
    assign_reinforcement,
    issue_orders,
    execute_orders,
    win
};

enum Action
{
    load_map,
    validate_map,
    add_player,
    assign_countries,
    issue_order,
    end_issue_orders,
    exec_order,
    end_exec_orders,
    win_game,
    play,
    end_game
};

class GameEngine
{
private:
    State state;

public:
    GameEngine();
    GameEngine(const GameEngine &g);
};

ostream &
operator<<(ostream &os, GameEngine &g);

#endif