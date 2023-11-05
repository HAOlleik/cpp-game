#include "Map.h"

Map::Map() : territories(std::make_shared<std::map<std::string, std::shared_ptr<Territory>>>()),
             continents(std::make_shared<std::map<std::string, std::shared_ptr<Continent>>>()),
             _pAuthor(std::make_shared<std::string>()),
             _pImage(std::make_shared<std::string>()),
             _wrap(std::make_shared<bool>(false)),
             _scroll(scroll::NONE)
{
}

Map::Map(const Map &map) : territories(map.territories),
                           continents(map.continents),
                           _pAuthor(map._pAuthor),
                           _pImage(map._pImage),
                           _wrap(map._wrap),
                           _scroll(map._scroll)
{
}

Map::~Map()
{
    territories = nullptr;
    continents = nullptr;

    _pAuthor = nullptr;
    _pImage = nullptr;
    _wrap = nullptr;
}

Map &Map::operator=(const Map &m)
{
    if (this != &m)
    {
        _pAuthor = m._pAuthor;
        _pImage = m._pImage;
        _wrap = m._wrap;
        territories = m.territories;
        continents = m.continents;
        _scroll = m._scroll;
    }
    return *this;
}

// Check if the entire map forms a connected graph.
int Map::_connectedGraph()
{
    if (territories->empty())
        return 1; // Empty map is trivially connected.

    std::set<Territory *> visited;
    std::deque<Territory *> queue;

    queue.push_back(territories->begin()->second.get()); // start with a random territory

    while (!queue.empty())
    {
        Territory *current = queue.front();
        queue.pop_front();

        if (visited.find(current) == visited.end())
        {
            visited.insert(current);
            const std::vector<std::shared_ptr<Territory>> &adjacentTerritories = current->getAdjacentTerritories();
            for (auto &adj : adjacentTerritories)
            {
                if (visited.find(adj.get()) == visited.end())
                {
                    queue.push_back(adj.get());
                }
            }
        }
    }

    return (visited.size() == territories->size()) ? 1 : 0;
}

// Check if a continent is connected subgraph
int Map::_connectedSubgraphs()
{
    for (const auto &contPair : *continents)
    {
        Continent *continent = contPair.second.get();
        const std::vector<std::shared_ptr<Territory>> &continentTerritories = continent->getTerritories();

        // Ensure the continent has territories before proceeding.
        if (continentTerritories.empty())
        {
            return 0; // A continent with no territories can't be considered connected.
        }

        // Apply BFS but limited to territories within the continent.
        std::set<Territory *> visited;
        std::deque<Territory *> queue;

        queue.push_back(continentTerritories[0].get());

        while (!queue.empty())
        {
            Territory *current = queue.front();
            queue.pop_front();

            if (current && visited.find(current) == visited.end())
            {
                visited.insert(current);
                const std::vector<std::shared_ptr<Territory>> &adjacentTerritories = current->getAdjacentTerritories();

                for (auto &adj : adjacentTerritories)
                {
                    // Only process if territory is unvisited and belongs to the current continent.
                    auto it = std::find_if(continentTerritories.begin(), continentTerritories.end(),
                                           [&adj](const std::shared_ptr<Territory> &territory)
                                           {
                                               return territory.get() == adj.get();
                                           });
                    if (adj && visited.find(adj.get()) == visited.end() &&
                        it != continentTerritories.end())
                    {
                        queue.push_back(adj.get());
                    }
                }
            }
        }

        if (visited.size() != continentTerritories.size())
            return 0; // Not all territories within the continent were visited.
    }

    return 1; // Every continent in the map is a connected subgraph.
}

int Map::_territoryBelongsToOneContinent()
{
    for (const auto &terrPair : *territories)
    {
        Territory *territory = terrPair.second.get();
        int count = 0;

        for (const auto &contPair : *continents)
        {
            Continent *continent = contPair.second.get();
            const std::vector<std::shared_ptr<Territory>> &continentTerritories = continent->getTerritories();

            // Check if the territory is in the current continent's territories
            auto it = std::find_if(continentTerritories.begin(), continentTerritories.end(),
                                   [territory](const std::shared_ptr<Territory> &t)
                                   {
                                       return t.get() == territory;
                                   });

            if (it != continentTerritories.end())
            {
                count++;
            }
        }

        if (count != 1)
            return 0;
    }

    return 1;
}

int Map::validate()
{
    return _connectedGraph() && _connectedSubgraphs() && _territoryBelongsToOneContinent();
}

// Add territory to the map
void Map::addTerritory(std::shared_ptr<Territory> t)
{
    territories->emplace(t->getName(), t);
}

std::shared_ptr<Territory> Map::getTerritory(const std::string &name)
{
    return territories->at(name);
}

std::shared_ptr<std::map<std::string, std::shared_ptr<Territory>>> &Map::getTerritories()
{
    return territories;
}

void Map::addContinent(std::shared_ptr<Continent> c)
{
    continents->emplace(c->getName(), c);
}

std::shared_ptr<Continent>
Map::getContinent(const std::string &name)
{
    return continents->at(name);
}

std::shared_ptr<std::map<std::string, std::shared_ptr<Continent>>> &Map::getContinents()
{
    return continents;
}

std::ostream &operator<<(std::ostream &os, const Map &m)
{
    for (const auto &elem : *(m.territories))
    {
        os << "MAP: " << elem.first << " " << elem.second->getName() << "\n";
    }
    for (const auto &elem : *(m.continents))
    {
        os << "CONTINENT: " << elem.first << " " << elem.second->getName() << "\n";
    }
    return os;
}