#ifndef MAP_H
#define MAP_H
#include <iostream>
using std::ostream;
#include <map>
#include <set>
#include <deque>

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
    void addTerritory(Territory *t);
    Territory *getTerritory(const std::string &name);
    void addContinent(Continent *c);
    Continent *getContinent(const std::string &name);
    std::map<std::string, Territory *> *territories;
    std::map<std::string, Continent *> *continents;

private:
    std::string *_pAuthor;
    std::string *_pImage;
    bool *_wrap;
    scroll _scroll;

    int _connectedGraph();
    int _connectedSubgraphs();
    int _countryBelongsToOneContinent();
};

ostream &operator<<(ostream &os, Map &m);
#endif