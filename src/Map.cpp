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
    // Use BFS or DFS to traverse the graph.
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

// Check if each continent forms a connected subgraph.
int Map::_connectedSubgraphs()
{
    std::cout << "we finished" << std::endl;

    for (auto &cont : *continents)
    {
        Continent *continent = cont.second;

        // Apply similar BFS or DFS but limited to territories within the continent.
        std::set<Territory *> visited;
        std::deque<Territory *> queue;

        queue.push_back(continent->getTerritories()[0]);

        while (!queue.empty())
        {
            Territory *current = queue.front();
            queue.pop_front();

            if (current && visited.find(current) == visited.end())
            {
                visited.insert(current);
                for (auto &adj : *(current->getAdjacentTerritories()))
                {
                    if (adj && visited.find(adj) == visited.end() &&
                        std::find(continent->getTerritories().begin(), continent->getTerritories().end(), adj) != continent->getTerritories().end())
                    {
                        queue.push_back(adj);
                    }
                }
            }
        }

        if (visited.size() != continent->getTerritories().size())
            return 0;
    }

    return 1;
}

// Check if each territory belongs to one and only one continent.
int Map::_territoryBelongsToOneContinent()
{
    std::cout << "we finished" << std::endl;

    for (auto &terr : *territories)
    {
        Territory *territory = terr.second;
        int count = 0;

        for (auto &cont : *continents)
        {
            Continent *continent = cont.second;
            if (std::find(continent->getTerritories().begin(), continent->getTerritories().end(), territory) != continent->getTerritories().end())
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
    return !(_connectedGraph() && _connectedSubgraphs() && _territoryBelongsToOneContinent());
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