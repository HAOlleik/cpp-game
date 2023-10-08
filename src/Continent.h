#include <string>
#include <vector>

#include "Territory.h"

class Continent
{
    std::string *name;
    int *score;
    std::vector<Territory *> *territories;

public:
    Continent(std::string *n);
    Continent(std::string *n, int *s);
    ~Continent();
    std::string getName();
    int getScore();
    std::vector<Territory *> getTerritories();
    void addTerritory(Territory *territory);
};
