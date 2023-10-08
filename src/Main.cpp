#include <iostream>

#include "MapLoader.h"
#include "Map.h"

// extern void testLoadMaps();

int main()
{
    // ::testLoadMaps();
    MapLoader loader;
    if (loader.load("/Users/avin/projects/university/comp345/project/maps/Alberta/Alberta.map"))
    {
        std::cout << "we finished" << std::endl;

        Map *gameMap = loader.getMap();
        // Further processing on gameMap...
        if (gameMap->validate())
        {
            std::cout << "The map is valid" << std::endl;
            return 0;
        }

        std::cout << "The loaded map is not valid" << std::endl;
        return 1;
    }
    std::cout << "Hello, World!!" << std::endl;

    return 0;
}