#include <string>
#include <vector>

#include "Territory.h"

class Continent
{
    std::string name;
    std::vector<Territory *> territories;

public:
    Continent(const std::string &n) : name(n) {}
    std::string getName();
    std::vector<Territory *> getTerritories();

    void addTerritory(Territory *territory)
    {
        territories.push_back(territory);
    }

    // Getter and setter methods...
};
