#include <string>
#include <vector>

#include "Player.h"

// Default Constructor
Territory::Territory() : name(""), owner(nullptr), armies(0) {}

// Constructor with Name
Territory::Territory(const std::string &n) : name(n), owner(nullptr), armies(0) {}

// Copy Constructor
Territory::Territory(const Territory &t) : name(t.name), owner(t.owner), armies(t.armies), adjacentTerritories(t.adjacentTerritories) {}

// Get name of the territory
std::string Territory::getName()
{
    return name;
}

// Add adjacent territory
void Territory::addAdjacent(Territory *territory)
{
    // It's a good practice to check for duplicates before adding.
    if (std::find(adjacentTerritories.begin(), adjacentTerritories.end(), territory) == adjacentTerritories.end())
    {
        adjacentTerritories.push_back(territory);
    }
}

// Return pointer to the vector of adjacent territories
std::vector<Territory *> Territory::getAdjacentTerritories()
{
    return adjacentTerritories; // Returning pointer to the first element in the vector.
}

// Overloaded stream insertion operator for Territory
ostream &operator<<(ostream &os, Territory &t)
{
    os << "Territory Name: " << t.getName() << "\n";
    os << "Owner: " << (t.owner ? t.owner->getName() : "None") << "\n"; // Assuming Player has a method `getName()`
    os << "Armies: " << t.armies << "\n";
    os << "Adjacent Territories: ";
    for (auto &adjTerr : t.adjacentTerritories)
    {
        os << adjTerr->getName() << " ";
    }
    return os;
}
