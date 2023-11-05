#include "Territory.h"

// Default Constructor
Territory::Territory() : name(std::make_unique<std::string>("")),
                         owner(nullptr),
                         armies(std::make_unique<int>(0)),
                         adjacentTerritories(std::make_unique<std::vector<std::weak_ptr<Territory>>>()) {}

// Constructor with Name
Territory::Territory(const std::string &nm) : name(std::make_unique<std::string>(nm)),
                                              owner(nullptr),
                                              armies(std::make_unique<int>(0)),
                                              adjacentTerritories(std::make_unique<std::vector<std::weak_ptr<Territory>>>()) {}

// Copy Constructor
Territory::Territory(const Territory &t)
{
    name = std::make_unique<std::string>(*t.name);
    owner = t.owner;
    armies = std::make_unique<int>(*t.armies);
    adjacentTerritories = std::make_unique<std::vector<std::weak_ptr<Territory>>>();
    for (const auto &sp : t.getAdjacentTerritories())
    {
        adjacentTerritories->push_back(std::weak_ptr<Territory>(sp));
    }
}

Territory::~Territory()
{
    name = nullptr;
    owner = nullptr;
    armies = nullptr;
    adjacentTerritories = nullptr;
}

// Copy Assignment Operator
Territory &Territory::operator=(const Territory &t)
{
    if (this != &t) // Prevent self-assignment
    {
        name = std::make_unique<std::string>(*t.name);
        owner = t.owner;
        armies = std::make_unique<int>(*t.armies);
        adjacentTerritories = std::make_unique<std::vector<std::weak_ptr<Territory>>>();
        for (const auto &sp : t.getAdjacentTerritories())
        {
            adjacentTerritories->push_back(std::weak_ptr<Territory>(sp));
        }
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
    auto territories = getAdjacentTerritories();
    // It's a good practice to check for duplicates before adding.
    if (std::find(territories.begin(), territories.end(), territory) == territories.end())
    {
        adjacentTerritories->push_back(territory);
    }
}

// Return the vector of adjacent territories
const std::vector<std::shared_ptr<Territory>> Territory::getAdjacentTerritories() const
{
    auto sharedVector = std::vector<std::shared_ptr<Territory>>();
    sharedVector.reserve(adjacentTerritories->size()); // Reserve space to avoid multiple reallocations.

    for (const auto &weakPtr : *adjacentTerritories)
    {
        if (auto sharedPtr = weakPtr.lock())
        {                                      // Check if the object is still alive.
            sharedVector.push_back(sharedPtr); // If it is, add to the new vector.
        }
        // If the object is no longer alive, the weak pointer cannot be locked and is skipped.
    }

    return sharedVector;
}

// Overloaded stream insertion operator for Territory
ostream &operator<<(ostream &os, const Territory &t)
{
    os << "Territory Name: " << t.getName() << "\n";
    os << "Owner: " << (t.owner ? t.owner->getName() : "None") << "\n";
    os << "Armies: " << *(t.armies) << "\n";
    os << "Adjacent Territories: ";
    for (const auto &adjTerr : t.getAdjacentTerritories())
    {
        os << adjTerr->getName() << " ";
    }
    return os;
}