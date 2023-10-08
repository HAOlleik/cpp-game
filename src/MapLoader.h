#ifndef MAP_LOADER_H
#define MAP_LOADER_H
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "MapLoader.h"
#include "Territory.h"
#include "Map.h"

// You can use the MapLoader like this:
// MapLoader loader;
// if(loader.load("path_to_map_file.map")) {
//     Map *gameMap = loader.getMap();
//     // Further processing on gameMap...
// }

class MapLoader
{
public:
    // Default constructor
    MapLoader();
    // Parametrized constr
    MapLoader(Map *map);
    // Copy constr
    MapLoader(const MapLoader &m);
    // Destructor
    ~MapLoader();
    // Map loader function
    bool load(const std::string &filepath);
    // Map getter
    Map *getMap() const;
    // Assignment operator overload
    MapLoader &operator=(MapLoader &m);

private:
    Map *map;
    // A helper function to trim whitespace.
    std::string trim(const std::string &s);
};

#endif