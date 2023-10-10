#include "MapLoader.h"

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

MapLoader::MapLoader() : map(std::make_shared<Map>()) {}

MapLoader::MapLoader(const std::shared_ptr<Map> &m) : map(m) {}

MapLoader::MapLoader(const MapLoader &m)
{
    map = m.getMap();
}

MapLoader::~MapLoader() {}

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
            auto continent = std::make_shared<Continent>(v[0], std::stoi(v[1]));
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
            auto terr = std::make_shared<Territory>(v[0]);
            map->addTerritory(terr);
            auto c = map->getContinent(v[3]);
            c->addTerritory(terr);
        }
    }

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

        std::shared_ptr<Territory> terr = map->getTerritory(v[0]);
        if (terr == nullptr)
        {
            std::cout << "Territory not found: " + v[0] << std::endl;
            continue;
        }
        //    0 1 2 3         4+
        // Name,-,-,Continent,Territory1A,Territory02,Territory04,Territory05
        if (v.size() < 5)
            continue; // meaning there are no interconnections
        int tc = 4;   // counter
        while (tc > 3 && (unsigned long)tc < v.size())
        {
            std::shared_ptr<Territory> t = map->getTerritory(v[tc]);
            if (t != nullptr)
            {
                terr->addAdjacent(t);
            }
            else
            {
                throw std::runtime_error("Territory not found");
            }
            tc++;
        }
    }
    // To print out the map
    auto &terri = *(map->getTerritories());
    for (const auto &elem : terri)
    {
        std::cout << "MAP:"
                  << " " << elem.first << " " << elem.second->getName() << "\n";
    }
    auto &cont = *(map->getContinents());
    if (!cont.empty())
    {
        for (const auto &elem : cont)
        {
            if (elem.second)
            {
                std::cout << "CONTINENT:"
                          << " " << elem.first << " " << elem.second->getName() << "\n";
                auto &cter = elem.second->getTerritories();
                for (const auto &elem : cter)
                {
                    std::cout << "CTER:"
                              << " " << elem->getName() << "\n";
                }
            }
            else
            {
                std::cout << "Error: Null Continent for key: " << elem.first << "\n";
            }
        }
    }
    else
    {
        std::cout << "Error: continents map is empty." << '\n';
    }

    file.close();
    return true;
}

std::shared_ptr<Map> MapLoader::getMap() const
{
    return map;
}

MapLoader &MapLoader::operator=(const MapLoader &m)
{
    map = m.getMap();
    return *this;
}