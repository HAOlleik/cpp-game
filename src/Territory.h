#ifndef TERRITORY_H
#define TERRITORY_H
#include <iostream>
using std::ostream;
#include <string>

#include "Player.h"

class Territory
{
public:
    std::string name;
    Player *owner;
    int armies;
    std::vector<Territory *> adjacentTerritories;

    Territory();
    Territory(const std::string &n);
    Territory(const Territory &t);
    std::string getName();
    void addAdjacent(Territory *territory);
    std::vector<Territory *> getAdjacentTerritories();
};

ostream &operator<<(ostream &os, Territory &t);

#endif