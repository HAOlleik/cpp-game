/*
You must deliver a file named MapDriver.cpp file that contains a free function named
testLoadMaps() that successively creates a map by reading a set of conquest map files and successfully
creates a map object for valid map files, and rejects various different invalid map files. After a map object has
been successfully created, the driver should demonstrate that the Map class implements the following
verifications: 1) the map is a connected graph, 2) continents are connected subgraphs, and 3) each country
belongs to one and only one continent.
*/
#include "Drivers.h"
#include "MapLoader.h"
#include "Map.h"

void testLoadMaps()
{
    MapLoader loader;
    std::shared_ptr<Map> gameMap;
    if (loader.load("maps/ABC_Map/ABC_Map.map"))
    {

        gameMap = loader.getMap();
        // Further processing on gameMap...
        if (gameMap->validate())
        {
            std::cout << "The map is valid" << std::endl;
            return;
        }

        std::cout << "The loaded map is not valid" << std::endl;
    }
};