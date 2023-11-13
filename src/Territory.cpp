#include "Territory.h"
#include "Player.h"

// Default Constructor
Territory::Territory() : _name(std::make_unique<std::string>("")),
                         _owner(nullptr),
                         _armies(std::make_unique<int>(0)),
                         _adjacentTerritories(std::make_unique<std::vector<std::weak_ptr<Territory>>>()) {}

// Constructor with Name
Territory::Territory(const std::string &nm) : _name(std::make_unique<std::string>(nm)),
                                              _owner(nullptr),
                                              _armies(std::make_unique<int>(0)),
                                              _adjacentTerritories(std::make_unique<std::vector<std::weak_ptr<Territory>>>()) {}

// Constructor with Name
Territory::Territory(
    const std::string &nm, std::shared_ptr<Continent> c) : _name(std::make_unique<std::string>(nm)),
                                                           _continent(c),
                                                           _owner(nullptr),
                                                           _armies(std::make_unique<int>(0)),

                                                           _adjacentTerritories(std::make_unique<std::vector<std::weak_ptr<Territory>>>())
{
}

// Copy Constructor
Territory::Territory(const Territory &t)
{
    _name = std::make_unique<std::string>(*t._name);
    _owner = t._owner;
    _armies = std::make_unique<int>(*t._armies);
    _adjacentTerritories = std::make_unique<std::vector<std::weak_ptr<Territory>>>();
    for (const auto &sp : t.getAdjacentTerritories())
    {
        _adjacentTerritories->push_back(std::weak_ptr<Territory>(sp));
    }
}

Territory::~Territory()
{
    _name = nullptr;
    _owner = nullptr;
    _armies = nullptr;
    _adjacentTerritories = nullptr;
}

// Copy Assignment Operator
Territory &Territory::operator=(const Territory &t)
{
    if (this != &t) // Prevent self-assignment
    {
        _name = std::make_unique<std::string>(*t._name);
        _owner = t._owner;
        _armies = std::make_unique<int>(*t._armies);
        _adjacentTerritories = std::make_unique<std::vector<std::weak_ptr<Territory>>>();
        for (const auto &sp : t.getAdjacentTerritories())
        {
            _adjacentTerritories->push_back(std::weak_ptr<Territory>(sp));
        }
    }
    return *this;
}

// Get name of the territory
std::string Territory::getName() const
{
    return *_name;
}

std::shared_ptr<Continent> Territory::getContinent() const
{
    return _continent;
}

std::shared_ptr<Player> Territory::getOwner() const
{
    return _owner;
}

int Territory::getArmies() const
{
    return *_armies;
}

void Territory::setArmies(int value)
{
    *_armies = value;
}

void Territory::setOwner(std::shared_ptr<Player> p)
{
    _owner = p;
}

// Add adjacent territory
void Territory::addAdjacent(std::shared_ptr<Territory> territory)
{
    auto territories = getAdjacentTerritories();
    // It's a good practice to check for duplicates before adding.
    if (std::find(territories.begin(), territories.end(), territory) == territories.end())
    {
        _adjacentTerritories->push_back(territory);
    }
}

// Return the vector of adjacent territories
const std::vector<std::shared_ptr<Territory>> Territory::getAdjacentTerritories() const
{
    auto sharedVector = std::vector<std::shared_ptr<Territory>>();
    sharedVector.reserve(_adjacentTerritories->size()); // Reserve space to avoid multiple reallocations.

    for (const auto &weakPtr : *_adjacentTerritories)
    {
        if (auto sharedPtr = weakPtr.lock())
        {                                      // Check if the object is still alive.
            sharedVector.push_back(sharedPtr); // If it is, add to the new vector.
        }
        // If the object is no longer alive, the weak pointer cannot be locked and is skipped.
    }

    return sharedVector;
}

const Territory *Territory::findAdjacentTerritory(Territory *t) const
{
    auto t = std::make_shared<Territory>(*t);
    auto found = std::find(_adjacentTerritories->begin(), _adjacentTerritories->end(), t);

    if (found != _adjacentTerritories->end())
    {
        // return raw locked poitner;
        return found->lock().get();
    }

    return nullptr;
}

// Overloaded stream insertion operator for Territory
ostream &operator<<(ostream &os, const Territory &t)
{
    os << "Territory Name: " << t.getName() << "\n";
    os << "Owner: " << (t._owner ? t._owner->getName() : "None") << "\n";
    os << "Armies: " << *(t._armies) << "\n";
    os << "Adjacent Territories: ";
    for (const auto &adjTerr : t.getAdjacentTerritories())
    {
        os << adjTerr->getName() << " ";
    }
    return os;
}