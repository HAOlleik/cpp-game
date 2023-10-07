#include <string>
#include <vector>

#include "Territory.h"

class Continent
{
    std::string name;
    int score;
    std::vector<Territory *> territories;

public:
    Continent(const std::string &n) : name(n), score(0) {}
    Continent(const std::string &n, int s) : name(n), score(s) {}
    std::string getName();
    std::vector<Territory *> getTerritories();

    void addTerritory(Territory *territory)
    {
        territories.push_back(territory);
    }

    // Getter and setter methods...
};
