#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
#include <iostream>
using std::ostream;
#include <memory>
#include <map>
#include <algorithm>
#include <random>
#include <vector>

#include "GameEngineState.h"
#include "Territory.h"
#include "Map.h"
#include "Cards.h"
#include "Command.h"
#include "CommandProcessing.h"
#include "MapLoader.h"
#include "Player.h"

#define MAX_PLAYERS 6

class GameEngine
{
public:
    GameEngine();                               // default
    GameEngine(const GameEngine &g);            // copy constr
    GameEngine(CommandProcessor cli);           // paratemtrized contructor
    GameEngine &operator=(const GameEngine &c); // assignment operator
    ~GameEngine();                              // destructor
    void startupPhase();                        // startup phase of the game

    void addPlayer(const std::string &playerName); // Part 3
    void setMap(std::shared_ptr<Map> map);         // Part 3

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
    // ACTION mainGameLoop();    // It is put in comment 2023-11-11
    void assignPlayersRandomOrder();
    void assignTerritoriesPlayers();
    void checkLoosers();
    void reinforcmentPhase();  // Part 3
    void issueOrdersPhase();   // Part 3
    void executeOrdersPhase(); // Part 3
    ACTION mainGameLoop();     // Part 3
    bool conditionToCheckForWinner();
};

void testMainGameLoop(); // Part 3

#endif
