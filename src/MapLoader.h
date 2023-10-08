#ifndef MAP_LOADER_H
#define MAP_LOADER_H
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "MapLoader.h"
#include "Territory.h"
#include "Map.h"

class MapLoader
{
public:
    MapLoader();
    bool load(const std::string &filepath);
    Map *getMap() const;

private:
    Map *map;

    std::string trim(const std::string &s);
};

#endif