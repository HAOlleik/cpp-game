#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <map>
#include <set>
#include <deque>
#include <vector>
#include <memory>
#include <algorithm>

#include "Territory.h"
#include "Continent.h"

enum scroll
{
    NONE,
    vertical,
    horizontal
};

#define MAX_NUMBER_CONTINENTS 32
#define MAX_TERRITORY_CONNECTIONS 10
#define MAX_NUMBER_TERRITORIES 255

class Map
{
public:
    Map();
    Map(const Map &map);
    ~Map();

    Map &operator=(const Map &m);

    int validate();
    void addTerritory(std::shared_ptr<Territory> t);
    std::shared_ptr<Territory> getTerritory(const std::string &name);
    std::shared_ptr<std::map<std::string, std::shared_ptr<Territory>>> &getTerritories();

    void addContinent(std::shared_ptr<Continent> c);
    std::shared_ptr<Continent> getContinent(const std::string &name);
    std::shared_ptr<std::map<std::string, std::shared_ptr<Continent>>> &getContinents();

    friend std::ostream &operator<<(std::ostream &os, const Map &m);

private:
    std::shared_ptr<std::map<std::string, std::shared_ptr<Territory>>> territories;
    std::shared_ptr<std::map<std::string, std::shared_ptr<Continent>>> continents;

    std::shared_ptr<std::string> _pAuthor;
    std::shared_ptr<std::string> _pImage;
    std::shared_ptr<bool> _wrap;
    scroll _scroll;

    int _connectedGraph();
    int _connectedSubgraphs();
    int _territoryBelongsToOneContinent();
};

std::ostream &operator<<(std::ostream &os, const Map &m);

#endif
