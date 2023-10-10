#ifndef MAP_LOADER_H
#define MAP_LOADER_H
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>

#include "MapLoader.h"
#include "Territory.h"
#include "Map.h"

class MapLoader
{
public:
    MapLoader();
    MapLoader(const std::shared_ptr<Map> &map);
    MapLoader(const MapLoader &m);
    ~MapLoader();
    bool load(const std::string &filepath);
    std::shared_ptr<Map> getMap() const;
    MapLoader &operator=(const MapLoader &m);

private:
    std::shared_ptr<Map> map;
    std::string trim(const std::string &s);
};

#endif