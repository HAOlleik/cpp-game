#ifndef MAP_H
#define MAP_H
#include <iostream>
using std::ostream;

#include "Territory.h"

enum scroll
{
    vertical,
    horizontal
};

#define MAX_NUMBER_CONTINENTS 32
#define MAX_TERRITORY_CONNECTIONS 10
#define MAX_NUMBER_TERRITORIES 255

class Map
{
private:
    char *_pAuthor;
    bool *_pWarn;
    char *_pImage;
    bool *_wrap;
    scroll _scroll;

    Territory _continents[];

    int _connectedGraph();
    int _connectedSubgraphs();
    int _countryBelongsToOneContinent();

public:
    Map();
    Map(const Map &map)
    {
        Map test = map;
    }
    int validate();
};

ostream &operator<<(ostream &os, Map &m);

#endif