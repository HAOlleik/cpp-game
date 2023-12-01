#include <string>
#include <vector>
#include <random>

#include "GameEngine.h"
#include "Drivers.h"
#include "PlayerStrategies.h"
#include "GlobalVariables.h"

//int mapTerritoriesCount = 0;

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
    testPlayerStrategies();

    return 0;
}
