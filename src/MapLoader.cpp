#include <fstream>
#include <sstream>

#include "Map.h"
#include "Territory.h"

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
        bool isReadingConnections = false;

        while (std::getline(file, line))
        {
            line = trim(line);

            if (line == "[countries]")
            {
                isReadingTerritories = true;
                continue;
            }
            else if (line == "[connections]")
            {
                isReadingTerritories = false;
                isReadingConnections = true;
                continue;
            }

            if (isReadingTerritories)
            {
                std::istringstream ss(line);
                std::string territoryName, continentName;
                ss >> territoryName >> continentName;
                // Create and add territory and continent to the map.
                Territory *territory = new Territory(territoryName);
                map->addTerritory(territory);
                if (map->getContinent(continentName) == nullptr)
                {
                    Continent *continent = new Continent(continentName);
                    map->addContinent(continent);
                }
                map->getContinent(continentName)->addTerritory(territory);
            }
            else if (isReadingConnections)
            {
                std::istringstream ss(line);
                std::string territoryName, adjacentTerritoryName;
                ss >> territoryName;
                Territory *territory = map->getTerritory(territoryName);
                while (ss >> adjacentTerritoryName)
                {
                    Territory *adjacentTerritory = map->getTerritory(adjacentTerritoryName);
                    territory->addAdjacent(adjacentTerritory);
                }
            }
        }

        file.close();
        return true;
    }

    Map *getMap() const
    {
        return map;
    }
};

// You can use the MapLoader like this:
// MapLoader loader;
// if(loader.load("path_to_map_file.map")) {
//     Map *gameMap = loader.getMap();
//     // Further processing on gameMap...
// }
