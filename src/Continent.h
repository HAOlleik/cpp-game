#ifndef CONTINENT_H
#define CONTINENT_H
#include <string>
#include <vector>

#include "Territory.h"

class Continent
{
    std::string *name;
    int *score;
    std::vector<Territory *> *territories;

public:
    // Deafult Consctructor
    Continent();
    // Parametrized constr
    Continent(std::string *n);
    // Parametrized constr
    Continent(std::string *n, int *s);
    // Copy Constructor
    Continent(const Continent &continent);
    // Destructor
    ~Continent();
    // Name getter
    std::string getName();
    // Score getter
    int getScore();
    // Territories getter
    std::vector<Territory *> getTerritories();
    // Add new territory
    void addTerritory(Territory *territory);
    // Assignemtn operator overload
    Continent &operator=(Continent &c);
};

#endif