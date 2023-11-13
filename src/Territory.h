#ifndef TERRITORY_H
#define TERRITORY_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
using std::ostream;
#include <string>

class Continent;
class Player;

class Territory
{
public:
    Territory();
    Territory(const std::string &n);
    Territory(const std::string &nm, std::shared_ptr<Continent> c);
    Territory(const Territory &t);            // Copy constructor
    Territory &operator=(const Territory &t); // Copy assignment operator
    ~Territory();

    std::string getName() const;
    std::shared_ptr<Continent> getContinent() const;
    std::shared_ptr<Player> getOwner() const;
    int getArmies() const;
    void setArmies(int);
    void setOwner(std::shared_ptr<Player> p);
    void addAdjacent(std::shared_ptr<Territory> territory);
    const Territory *findAdjacentTerritory(Territory *) const;
    const std::vector<std::shared_ptr<Territory>> getAdjacentTerritories() const;
    friend ostream &operator<<(ostream &os, const Territory &t);

private:
    std::unique_ptr<std::string> _name;
    std::shared_ptr<Continent> _continent;
    std::shared_ptr<Player> _owner; // fix other p refs
    std::unique_ptr<int> _armies;
    std::unique_ptr<std::vector<std::weak_ptr<Territory>>> _adjacentTerritories;
};

#endif