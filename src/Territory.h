#ifndef TERRITORY_H
#define TERRITORY_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
using std::ostream;
#include <string>

#include "Player.h"
// class Player;

class Territory
{
public:
    Territory();
    Territory(const std::string &n);
    Territory(const Territory &t);            // Copy constructor
    Territory &operator=(const Territory &t); // Copy assignment operator
    ~Territory();

    std::string getName() const;
    void setOwner(std::shared_ptr<Player> p);
    void addAdjacent(std::shared_ptr<Territory> territory);
    const std::vector<std::shared_ptr<Territory>> getAdjacentTerritories() const;
    friend ostream &operator<<(ostream &os, const Territory &t);

private:
    std::unique_ptr<std::string> _name;
    std::shared_ptr<Player> _owner; // fix other p refs
    std::unique_ptr<int> _armies;
    std::unique_ptr<std::vector<std::weak_ptr<Territory>>> _adjacentTerritories;
};

#endif