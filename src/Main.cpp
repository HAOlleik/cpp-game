#include <string>
#include <vector>

#include "GameEngine.h"
#include "Drivers.h"
#include "PlayerStrategies.h"

int main(int argc, char *argv[])
{
    vector<string> arguments(argv, argv + argc);
    // testOrdersLists();
    // testPlayers();
    // testCards();
    // testLoadMaps();
    // testCommandProcessor(arguments, arguments.size());
    // testGameEngineStates();
    // testMainGameLoop();
    // testLoggingObserver();

    GameEngine game;
    MapLoader loader;
    loader.load("maps/Alberta/Alberta.map");
    game.setMap(loader.getMap());
    string name = "pl1";
    Player *player = new Player(&name);
    auto terr = _map->getTerritories();

    uint64_t iter = 0;
    for (auto &it : *terr)
    {
        it.second->setOwner(_players[iter % _players.size()]);
        // add terr pointer to player
        _players[iter % _players.size()]->setTerritories(it.second.get());
        iter++;
    }
    player->setReinforcementPool(10);
    std::string strategyName = "";
    while (true)
    {
        cout << "Next\n";
        cin >> strategyName;
        PlayerStrategy *strategy = PlayerStrategy::handleStrategyCreation(player, strategyName);
        cout << *strategy << endl;
        strategy->issueOrder();
    }

    return 0;
}
