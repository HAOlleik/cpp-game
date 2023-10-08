#include "Continent.h"

Continent::Continent() : name(new std::string()), score(new int(0)), territories(new std::vector<Territory *>()) {}

Continent::Continent(std::string *n) : name(new std::string(*n)), score(new int(0)), territories(new std::vector<Territory *>()) {}

Continent::Continent(std::string *n, int *s) : name(new std::string(*n)), score(new int(*s)), territories(new std::vector<Territory *>()) {}

Continent::Continent(const Continent &c)
{
    name = c.name;
    score = c.score;
    territories = c.territories;
}

Continent::~Continent()
{
    delete name;
    delete score;
    for (auto &terr : *territories)
    {
        delete terr;
    }
    delete territories;
}
std::string Continent::getName()
{
    return *name;
}

int Continent::getScore()
{
    return *score;
}

std::vector<Territory *> Continent::getTerritories()
{
    return *territories;
}

void Continent::addTerritory(Territory *territory)
{
    (*territories).push_back(territory);
}

Continent &Continent::operator=(Continent &c)
{
    name = c.name;
    score = c.score;
    territories = c.territories;

    return *this;
}
