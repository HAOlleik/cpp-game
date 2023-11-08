#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
#include <iostream>
using std::ostream;
// #include <bits/stdc++.h>
#include <memory>
#include <map>
#include "algorithm"

#include "Player.h"
#include "Map.h"
#include "Command.h"
#include "CommandProcessing.h"
#include "MapLoader.h"
#include "Cards.h"
#include "GameEngineState.h"

#define MAX_PLAYERS = 6

class GameEngine
{
public:
    GameEngine();                               // default
    GameEngine(const GameEngine &g);            // copy constr
    GameEngine(CommandProcessor cli);           // paratemtrized contructor
    GameEngine &operator=(const GameEngine &c); // assignment operator
    ~GameEngine();                              // destructor
    void startupPhase();                        // startup phase of the game

    STATE *getState() const // getter for state
    {
        return _state.get();
    };
    void setState(STATE *newState) // setter for state
    {
        _state = std::make_shared<STATE>(*newState);
    };
    friend ostream &operator<<(ostream &os, GameEngine &g);

private:
    std::shared_ptr<STATE> _state = NULL;
    std::vector<shared_ptr<Player>> _players;
    std::unique_ptr<Map> _map = NULL;
    std::unique_ptr<CommandProcessor> _cli = NULL;
    std::unique_ptr<Deck> _deck;
    ACTION mainGameLoop();
    void randomOrder();
    void assignTerritories();
};

#endif
