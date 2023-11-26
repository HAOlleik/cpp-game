#include <string>
#include <vector>
#include <random>

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
    string name1 = "pl1";
    string name2 = "pl2";
    Player *player1 = new Player(&name1);
    Player *player2 = new Player(&name2);
    auto terr = loader.getMap()->getTerritories();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    uint64_t iter = 0;
    for (auto &it : *terr)
    {
        if (dis(gen) == 0)
        {
            player1->setTerritories(it.second.get());
        }
        else
        {
            player2->setTerritories(it.second.get());
        }
        iter++;
    }
    player1->setReinforcementPool(50);
    player2->setReinforcementPool(50);
    std::string strategyName = "";
    while (true)
    {
        cout << "Next\n";
        cin >> strategyName;
        PlayerStrategy *strategy1 = PlayerStrategy::handleStrategyCreation(player1, strategyName);
        PlayerStrategy *strategy2 = PlayerStrategy::handleStrategyCreation(player2, strategyName);
        cout << *strategy1 << endl;
        // cout << "Territories to defend1: " << endl;
        // for (auto &t : strategy1->toDefend())
        // {
        //     cout << *t << endl;
        // }
        // cout << "\n\nTerritories to defend2: " << endl;
        // for (auto &t : strategy2->toDefend())
        // {
        //     cout << *t << endl;
        // }
        // cout << "\n\nTerritories to attack1: " << endl;
        // for (auto &t : strategy1->toAttack())
        // {
        //     cout << *t << endl;
        // }
        // cout << "\n\nTerritories to attack2: " << endl;
        // for (auto &t : strategy2->toAttack())
        // {
        //     cout << *t << endl;
        // }
        strategy1->issueOrder();
    }

    return 0;
}
