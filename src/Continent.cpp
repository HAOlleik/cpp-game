#include "Continent.h"
#include "Territory.h"

Continent::Continent() : name(std::make_unique<std::string>()),
                         score(std::make_unique<int>(0)),
                         territories(std::make_unique<std::vector<std::shared_ptr<Territory>>>()) {}

Continent::Continent(const std::string &n) : name(std::make_unique<std::string>(n)), score(std::make_unique<int>(0)), territories(std::make_unique<std::vector<std::shared_ptr<Territory>>>()) {}

Continent::Continent(const std::string &n, int s) : name(std::make_unique<std::string>(n)), score(std::make_unique<int>(s)), territories(std::make_unique<std::vector<std::shared_ptr<Territory>>>()) {}

Continent::Continent(const Continent &c) : name(std::make_unique<std::string>(*c.name)), score(std::make_unique<int>(*c.score)), territories(std::make_unique<std::vector<std::shared_ptr<Territory>>>(*c.territories)) {}

Continent::~Continent()
{
    name = nullptr;
    score = nullptr;
    territories = nullptr;
}

Continent &Continent::operator=(const Continent &c)
{
    if (this != &c)
    {
        name = std::make_unique<std::string>(*c.name);
        score = std::make_unique<int>(*c.score);
        territories = std::make_unique<std::vector<std::shared_ptr<Territory>>>(*c.territories);
    }
    return *this;
}

std::string Continent::getName() const
{
    return *name;
}

int Continent::getScore() const
{
    return *score;
}

const std::vector<std::shared_ptr<Territory>> &Continent::getTerritories() const
{
    return *territories;
}

void Continent::addTerritory(std::shared_ptr<Territory> territory)
{
    territories->push_back(territory);
}