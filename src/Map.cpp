#include "Map.h"

// Default Constructor
Map::Map()
{
    _pAuthor = new std::string();
    _pImage = new std::string();
    _wrap = new bool(false);
    territories = new std::map<std::string, Territory *>();
    continents = new std::map<std::string, Continent *>();
    _scroll = scroll::NONE;
}

// Copy Constructor
Map::Map(const Map &map)
{
    _pAuthor = new std::string(*(map._pAuthor));
    _pImage = new std::string(*(map._pImage));
    _wrap = new bool(*(map._wrap));
    territories = new std::map<std::string, Territory *>(*(map.territories));
    continents = new std::map<std::string, Continent *>(*(map.continents));
    _scroll = map._scroll;
}

// Destructor
Map::~Map()
{
    delete _pAuthor;
    delete _pImage;
    delete _wrap;

    for (auto &pair : *territories)
    {
        delete pair.second;
    }
    delete territories;

    for (auto &pair : *continents)
    {
        delete pair.second;
    }
    delete continents;
}

// Overloaded assignment operator
Map &Map::operator=(const Map &m)
{
    if (this != &m)
    {
        // Deep copy contents from 'm' to 'this' object
        *_pAuthor = *(m._pAuthor);
        *_pImage = *(m._pImage);
        *_wrap = *(m._wrap);

        // Cleanup current territories and continents before copying
        for (auto &pair : *territories)
        {
            delete pair.second;
        }
        territories->clear();
        for (auto &pair : *continents)
        {
            delete pair.second;
        }
        continents->clear();

        // Deep copy territories and continents
        *territories = *(m.territories);
        *continents = *(m.continents);

        _scroll = m._scroll;
    }
    return *this;
}

// Check if the entire map forms a connected graph.
int Map::_connectedGraph()
{
    // Use BFS to traverse the graph.
    // If all territories are visited, it's connected.

    if (territories->empty())
        return 1; // Empty map is trivially connected.

    std::set<Territory *> visited;
    std::deque<Territory *> queue;

    queue.push_back(territories->begin()->second); // start with a random territory

    while (!queue.empty())
    {
        Territory *current = queue.front();
        queue.pop_front();

        if (visited.find(current) == visited.end())
        {
            visited.insert(current);
            for (auto &adj : *(current->getAdjacentTerritories()))
            {
                if (visited.find(adj) == visited.end())
                {
                    queue.push_back(adj);
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
        Continent *continent = contPair.second;
        const std::vector<Territory *> &continentTerritories = continent->getTerritories();

        // Ensure the continent has territories before proceeding.
        if (continentTerritories.empty())
        {
            return 0; // A continent with no territories can't be considered connected.
        }

        // Apply BFS but limited to territories within the continent.
        std::set<Territory *> visited;
        std::deque<Territory *> queue;

        queue.push_back(continentTerritories[0]);

        while (!queue.empty())
        {
            Territory *current = queue.front();
            queue.pop_front();

            if (current && visited.find(current) == visited.end())
            {
                visited.insert(current);
                const std::vector<Territory *> &adjacentTerritories = *(current->getAdjacentTerritories());

                for (Territory *adj : adjacentTerritories)
                {
                    // Only process if territory is unvisited and belongs to the current continent.
                    if (adj && visited.find(adj) == visited.end() &&
                        std::find(continentTerritories.begin(), continentTerritories.end(), adj) != continentTerritories.end())
                    {
                        queue.push_back(adj);
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
        Territory *territory = terrPair.second;
        int count = 0;

        for (const auto &contPair : *continents)
        {
            Continent *continent = contPair.second;
            const std::vector<Territory *> &continentTerritories = continent->getTerritories();

            // Check if the territory is in the current continent's territories
            if (std::find(continentTerritories.begin(), continentTerritories.end(), territory) != continentTerritories.end())
            {
                count++;
            }
        }

        if (count != 1)
            return 0;
    }

    return 1;
}

// Add territory to the map
void Map::addTerritory(Territory *t)
{
    (*territories)[t->getName()] = t;
}

// Retrieve territory by name
Territory *Map::getTerritory(const std::string &name)
{
    if (territories->find(name) != territories->end())
    {
        return (*territories)[name];
    }
    else
    {
        return nullptr;
    }
}

// Add continent to the map
void Map::addContinent(Continent *c)
{
    (*continents)[c->getName()] = c;
}

// Retrieve continent by name
Continent *Map::getContinent(const std::string &name)
{
    if (continents->find(name) != continents->end())
    {
        return (*continents)[name];
    }
    else
    {
        throw std::runtime_error("Continent not found"); // Consider handling this exception in calling functions
    }
}

std::map<std::string, Territory *> *Map::_getTerritories()
{
    return territories;
}
std::map<std::string, Continent *> *Map::_getContinents()
{
    return continents;
}

// Validate map by all parameters
int Map::validate()
{
#include <iostream>
    std::cout << _connectedGraph() << ' ' << _connectedSubgraphs() << ' ' << _territoryBelongsToOneContinent();
    return _connectedGraph() && _connectedSubgraphs() && _territoryBelongsToOneContinent();
}

ostream &operator<<(ostream &os, Map &m)
{
    // To print out the map
    std::map<std::string, Territory *> *terri = m._getTerritories();
    for (const auto &elem : *terri)
    {
        os << "MAP:"
           << " " << elem.first << " " << elem.second->getName() << "\n";
    }
    std::map<std::string, Continent *> *cont = m._getContinents();
    if (cont)
    {
        for (const auto &elem : *cont)
        {
            if (elem.second)
            {
                os << "CONTINENT:"
                   << " " << elem.first << " " << elem.second->getName() << "\n";
            }
            else
            {
                os << "Error: Null Continent for key: " << elem.first << "\n";
            }
        }
    }
    else
    {
        os << "Error: continents map is nullptr." << '\n';
    }
    return os;
}

Map &Map::operator=(Map &m)
{
    _pAuthor = m._pAuthor;
    _pImage = m._pImage;
    _wrap = m._wrap;
    _scroll = m._scroll;
    territories = m.territories;
    continents = m.continents;

    return *this;
}