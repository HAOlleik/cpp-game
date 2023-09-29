#ifndef TERRITORY_H
#define TERRITORY_H
#include <iostream>
using std::ostream;

class Territory
{
public:
    Territory();
    Territory(const Territory &t);
};

ostream &operator<<(ostream &os, Territory &t);

#endif