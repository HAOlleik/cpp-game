#ifndef CONTINENT_H
#define CONTINENT_H
#include <string>
#include <vector>
#include <memory>

#include "Territory.h"

class Continent
{
private:
    std::unique_ptr<std::string> name;
    std::unique_ptr<int> score;
    std::unique_ptr<std::vector<std::shared_ptr<Territory>>> territories;

public:
    Continent();
    Continent(const std::string &n);
    Continent(const std::string &n, int s);
    Continent(const Continent &c);
    Continent &operator=(const Continent &c);
    ~Continent();

    std::string getName() const;
    int getScore() const;
    const std::vector<std::shared_ptr<Territory>> &getTerritories() const;
    void addTerritory(std::shared_ptr<Territory> territory);
};

#endif