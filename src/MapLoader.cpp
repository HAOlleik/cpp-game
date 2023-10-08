#include <fstream>
#include <sstream>
#include <iostream>

#include "MapLoader.h"
#include "Territory.h"

// You can use the MapLoader like this:
// MapLoader loader;
// if(loader.load("path_to_map_file.map")) {
//     Map *gameMap = loader.getMap();
//     // Further processing on gameMap...
// }

// A helper function to trim whitespace.
std::string MapLoader::trim(const std::string &s)
{
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start))
    {
        start++;
    }

    auto end = s.end();
    do
    {
        end--;
    } while (end != start && std::isspace(*end));

    return std::string(start, end + 1);
}

MapLoader::MapLoader() : map(new Map()) {}

bool MapLoader::load(const std::string &filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Error: Couldn't open the file!" << std::endl;
        return false;
    }

    std::string line;
    bool isReadingTerritories = false;
    bool isReadingContinents = false;

    while (std::getline(file, line))
    {
        // safegaurd against empty lines at the end of the file
        if (line.length() < 2)
            continue;

        line = trim(line);
        if (line == "[Continents]")
        {
            isReadingContinents = true;
            continue;
        }
        else if (line == "[Territories]")
        {
            isReadingContinents = false;
            isReadingTerritories = true;
            continue;
        }

        if (isReadingContinents)
        {
            std::istringstream ss(line);
            std::string s;
            std::vector<std::string> v;
            while (std::getline(ss, s, '='))
            {
                v.push_back(s);
            }
            // Create continent
            Continent *continent = new Continent(&v[0], new int(atoi(v[1].c_str())));
            map->addContinent(continent);
        }
        else if (isReadingTerritories)
        {
            std::istringstream ss(line);
            std::string s;
            std::vector<std::string> v;
            while (std::getline(ss, s, ','))
            {
                v.push_back(s);
            };
            // Create Territory
            Territory *terr = new Territory(&v[0]);
            map->addTerritory(terr);
            Continent *c = map->getContinent(v[3]);
            c->addTerritory(terr);
        }
    }
    // To print out the map
    // std::map<std::string, Territory *> *terri = map->territories;
    // for (const auto &elem : *terri)
    // {
    //     std::cout << "MAP:"
    //               << " " << elem.first << " " << elem.second->getName() << "\n";
    // }
    // std::map<std::string, Continent *> *cont = map->continents;
    // if (cont)
    // {
    //     for (const auto &elem : *cont)
    //     {
    //         if (elem.second)
    //         {
    //             std::cout << "CONTINENT:"
    //                       << " " << elem.first << " " << elem.second->getName() << "\n";
    //         }
    //         else
    //         {
    //             std::cout << "Error: Null Continent for key: " << elem.first << "\n";
    //         }
    //     }
    // }
    // else
    // {
    //     std::cout << "Error: continents map is nullptr." << '\n';
    // }

    // doing second pass to interconnect territories since we created all of them
    file.clear();  // clear flags
    file.seekg(0); // start from the beggining
    isReadingTerritories = false;

    while (std::getline(file, line))
    {
        // safegaurd against empty lines at the end of the file
        if (line.length() < 2)
        {
            continue;
        }

        // find [Territories]
        line = trim(line);
        if (line == "[Territories]")
        {
            isReadingTerritories = true;
            continue;
        }
        if (!isReadingTerritories)
        {
            continue;
        }

        std::istringstream ss(line);
        std::string s;
        std::vector<std::string> v;
        while (std::getline(ss, s, ','))
        {
            v.push_back(s);
        };

        Territory *terr = map->getTerritory(v[0]);
        if (terr == nullptr)
        {
            std::cout << "Territory not found: " + v[0] << std::endl;
            continue;
        }
        // std::cout << "origin " << terr->getName() << std::endl;
        //    0 1 2 3         4+
        // Name,-,-,Continent,Territory1A,Territory02,Territory04,Territory05
        if (v.size() < 5)
            continue; // meaning there are no interconnections
        int tc = 4;   // counter
        while (tc > 3 && (unsigned long)tc < v.size())
        {
            // std::cout << line << std::endl;
            // std::cout << tc << std::endl;
            // std::cout << v.size() << std::endl;

            Territory *t = map->getTerritory(v[tc]);
            // std::cout << "counter " << tc << " looking for" << v[tc] << " " << t->getName() << std::endl;
            if (t != nullptr)
            {
                terr->addAdjacent(t);
            }
            tc++;
        }
    }

    file.close();
    return true;
}

Map *MapLoader::getMap() const
{
    return map;
}
