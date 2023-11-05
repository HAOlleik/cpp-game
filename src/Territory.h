#ifndef TERRITORY_H
#define TERRITORY_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
using std::ostream;
#include <string>

// #include "Player.h"
class Player;

class Territory
{
public:
    Territory();
    Territory(const std::string &n);
    Territory(const Territory &t);            // Copy constructor
    Territory &operator=(const Territory &t); // Copy assignment operator
    ~Territory();

    std::string getName() const;
    void addAdjacent(std::shared_ptr<Territory> territory);
    const std::vector<std::shared_ptr<Territory>> getAdjacentTerritories() const;
    friend ostream &operator<<(ostream &os, const Territory &t);

private:
    std::unique_ptr<std::string> name;
    Player *owner;
    std::unique_ptr<int> armies;
    std::unique_ptr<std::vector<std::weak_ptr<Territory>>> adjacentTerritories;
};

#endif