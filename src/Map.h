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
    // Default constr
    Map();
    // Copy constr
    Map(const Map &map);
    // Destruct
    ~Map();
    // Operator overlead
    Map &operator=(const Map &m);
    // Validate map method
    int validate();
    // Add territory to map
    void addTerritory(Territory *t);
    // Getter terrtiroy
    Territory *getTerritory(const std::string &name);
    // Getter for all territories
    std::map<std::string, Territory *> *_getTerritories();
    // Add continent method
    void
    addContinent(Continent *c);
    // Getter continents
    Continent *getContinent(const std::string &name);
    // Getter for all continents
    std::map<std::string, Continent *> *_getContinents();
    // Assignment Operator overload
    Map &operator=(Map &m);
    friend ostream &operator<<(ostream &os, const Map &m);

private:
    std::map<std::string, Territory *> *territories;
    std::map<std::string, Continent *> *continents;

    std::string *_pAuthor;
    std::string *_pImage;
    bool *_wrap;
    scroll _scroll;

    int _connectedGraph();
    int _connectedSubgraphs();
    int _territoryBelongsToOneContinent();
};

ostream &operator<<(ostream &os, const Map &m);
#endif