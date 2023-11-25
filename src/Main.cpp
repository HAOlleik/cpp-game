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

    string name = "pl1";
    Player *player = new Player(&name);
    std::string strategyName = "human";
    while (true)
    {
        cout << "Next\n";
        cin >> strategyName;
        PlayerStrategy *strategy = PlayerStrategy::handleStrategyCreation(player, strategyName);
    }

    return 0;
}
