#include <string>
#include <vector>

#include "GameEngine.h"
#include "Drivers.h"

int main(int argc, char *argv[])
{
    vector<string> arguments(argv, argv + argc);
    // testOrdersLists();
    // testPlayers();
    // testCards();
    // testLoadMaps();
    testCommandProcessor(arguments, arguments.size());
    // testGameEngineStates();
    //testMainGameLoop();
    testLoggingObserver();

    return 0;
}
