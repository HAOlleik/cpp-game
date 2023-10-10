#include "Territory.h"

// Default Constructor
Territory::Territory() : name(std::make_unique<std::string>("")),
                         owner(nullptr),
                         armies(std::make_unique<int>(0)),
                         adjacentTerritories(std::make_unique<std::vector<std::shared_ptr<Territory>>>()) {}

// Constructor with Name
Territory::Territory(const std::string &nm) : name(std::make_unique<std::string>(nm)),
                                              owner(nullptr),
                                              armies(std::make_unique<int>(0)),
                                              adjacentTerritories(std::make_unique<std::vector<std::shared_ptr<Territory>>>()) {}

// Copy Constructor
Territory::Territory(const Territory &t)
{
    name = std::make_unique<std::string>(*t.name);
    owner = t.owner;
    armies = std::make_unique<int>(*t.armies);
    adjacentTerritories = std::make_unique<std::vector<std::shared_ptr<Territory>>>(*t.adjacentTerritories);
}

// Copy Assignment Operator
Territory &Territory::operator=(const Territory &t)
{
    if (this != &t) // Prevent self-assignment
    {
        name = std::make_unique<std::string>(*t.name);
        owner = t.owner;
        armies = std::make_unique<int>(*t.armies);
        adjacentTerritories = std::make_unique<std::vector<std::shared_ptr<Territory>>>(*t.adjacentTerritories);
    }
    return *this;
}

// Get name of the territory
std::string Territory::getName() const
{
    return *name;
}

// Add adjacent territory
void Territory::addAdjacent(std::shared_ptr<Territory> territory)
{
    // It's a good practice to check for duplicates before adding.
    if (std::find(adjacentTerritories->begin(), adjacentTerritories->end(), territory) == adjacentTerritories->end())
    {
        adjacentTerritories->push_back(territory);
    }
}

// Return the vector of adjacent territories
const std::vector<std::shared_ptr<Territory>> &Territory::getAdjacentTerritories() const
{
    return *adjacentTerritories;
}

// Overloaded stream insertion operator for Territory
ostream &operator<<(ostream &os, const Territory &t)
{
    os << "Territory Name: " << t.getName() << "\n";
    os << "Owner: " << (t.owner ? t.owner->getName() : "None") << "\n";
    os << "Armies: " << *(t.armies) << "\n";
    os << "Adjacent Territories: ";
    for (const auto &adjTerr : *t.adjacentTerritories)
    {
        os << adjTerr->getName() << " ";
    }
    return os;
}