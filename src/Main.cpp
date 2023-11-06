#include <iostream>

// #include "Order.h"
#include "Drivers.h"
// #include "GameEngine.h"

int main(int argc, char* argv[])
{
    // testOrdersLists();
    // testPlayers();
    // testCards();
    // testLoadMaps();

    vector<string> arguments(argv, argv + argc);

    for (size_t i = 1; i < arguments.size(); ++i) {
        if (arguments[i] == "-console" || arguments[i] == "--c") {
            testCommandProcessor();
        } else if (arguments[i] == "-file" || arguments[i] == "--f") {
            string filename = arguments[i + 1];
            if (filename.empty()) {
                std::cerr << "Error: No filename provided for file mode. Usage: -file <filename> or --f <filename>" << std::endl;
                return 1;
            }
            testCommandProcessor(filename);
        } else {
            testCommandProcessor();
        }
    }

    testGameEngineStates();
    
    return 0;
}