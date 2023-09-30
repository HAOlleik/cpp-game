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