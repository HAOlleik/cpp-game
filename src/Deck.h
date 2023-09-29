#ifndef DECK_H
#define DECK_H
#include <queue>
using std::queue;
#include <iostream>
using std::ostream;

#include "Card.h"

class Deck
{
private:
public:
    Deck();
    Deck(const Deck &o);
    Card *draw();
    void remove();
    void execute();
};

ostream &operator<<(ostream &os, Deck &o);

#endif