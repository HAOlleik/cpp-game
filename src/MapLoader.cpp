#include <fstream>
#include <sstream>

#include "Map.h"
#include "Territory.h"

// You can use the MapLoader like this:
// MapLoader loader;
// if(loader.load("path_to_map_file.map")) {
//     Map *gameMap = loader.getMap();
//     // Further processing on gameMap...
// }
class MapLoader
{
    Map *map;

    // A helper function to trim whitespace.
    std::string trim(const std::string &s)
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

public:
    MapLoader() : map(new Map()) {}

    bool load(const std::string &filePath)
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
            line = trim(line);

            if (line == "[Continents]")
            {
                isReadingContinents = true;
                continue;
            }
            else if (line == "[Territories]")
            {
                isReadingContinents = true;
                isReadingTerritories = false;
                continue;
            }

            if (isReadingContinents)
            {
                std::istringstream ss(line);
                std::string s;
                vector<string> v;
                while (std::getline(ss, s, ','))
                {
                    v.push_back(s);
                }
                // Create continent
                Continent *continent = new Continent(v[0], atoi(v[1].c_str()));
                map->addContinent(continent);
            }
            else if (isReadingTerritories)
            {
                std::istringstream ss(line);
                std::string s;
                vector<string> v;
                while (std::getline(ss, s, ','))
                {
                    v.push_back(s);
                };
                // Create Territory
                Territory *terr = new Territory(v[0]);
                Continent *c = map->getContinent(v[3]);
                c->addTerritory(terr);
            }
        }

        // doing second pass to interconnect territories since we created all of them
        file.clear();  // clear flags
        file.seekg(0); // start from the beggining
        isReadingTerritories = false;
        while (std::getline(file, line))
        {
            // find [Territories]
            if (line != "[Territories]" && !isReadingTerritories)
            {
                isReadingTerritories = true;
                continue;
            }
            std::istringstream ss(line);
            std::string s;
            vector<string> v;
            while (std::getline(ss, s, ','))
            {
                v.push_back(s);
            };
            //    0 1 2 3         4+
            // Name,-,-,Continent,Territory1A,Territory02,Territory04,Territory05
            Territory *terr = map->getTerritory(v[0]);
            if (v.size() < 5)
                continue; // meaning there are no interconnections
            int tc = 5;   // counter
            do
            {
                terr->addAdjacent(map->getTerritory(v[tc])); // add pointer to adjacent territory

            } while ((unsigned long)tc <= v.size());
        }

        file.close();
        return true;
    }

    Map *getMap() const
    {
        return map;
    }
};
