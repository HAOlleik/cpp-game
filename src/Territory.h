#ifndef TERRITORY_H
#define TERRITORY_H
#include <iostream>
#include <vector>
#include <algorithm>
using std::ostream;
#include <string>

// Forward declaration
class Player;

class Territory
{
public:
    std::string *name;
    Player *owner;
    int *armies;
    std::vector<Territory *> *adjacentTerritories;

    // Default consrt
    Territory();
    // Parametrized constr
    Territory(const std::string *n);
    // Copy consrt
    Territory(const Territory &t);
    // Getter name
    std::string getName();
    // Add adjacent terrtiroy
    void addAdjacent(Territory *territory);
    // Getter adjacent territories
    std::vector<Territory *> *getAdjacentTerritories();
    Territory &operator=(Territory &t);
};

ostream &operator<<(ostream &os, Territory &t);

#endif