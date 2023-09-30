#pragma once
#include <iostream>
using std::ostream;

class Territory
{
public:
	Territory();
	Territory(const Territory& t);
};

ostream& operator<<(ostream& os, Territory& t);