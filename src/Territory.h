#ifndef TERRITORY_H
#define TERRITORY_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
using std::ostream;
#include <string>

// Forward declaration
#include "Player.h"

class Territory
{
public:
    std::unique_ptr<std::string> name;
    Player *owner;
    std::unique_ptr<int> armies;
    std::unique_ptr<std::vector<std::shared_ptr<Territory>>> adjacentTerritories;

    Territory();
    Territory(const std::string &n);
    Territory(const Territory &t);            // Copy constructor
    Territory &operator=(const Territory &t); // Copy assignment operator
    ~Territory() = default;

    std::string getName() const;
    void addAdjacent(std::shared_ptr<Territory> territory);
    const std::vector<std::shared_ptr<Territory>> &getAdjacentTerritories() const;
};

ostream &operator<<(ostream &os, const Territory &t);

#endif