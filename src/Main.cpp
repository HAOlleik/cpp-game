#include <iostream>

// #include "Order.h"
#include "Drivers.h"
// #include "GameEngine.h"

int main(int argc, char *argv[])
{
    vector<string> arguments(argv, argv + argc);
    // testOrdersLists();
    // testPlayers();
    // testCards();
    // testLoadMaps();
    testCommandProcessor(arguments, arguments.size());
    // testGameEngineStates();
    testMainGameLoop();

    return 0;
}
