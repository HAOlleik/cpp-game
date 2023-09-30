#ifndef DECK_H
#define DECK_H
#include <queue>
using std::queue;
#include <iostream>
using std::ostream;

#include "Card.h"
#include "Player.h"

class Deck
{
private:
    Player *_player;

public:
    Deck();
    Deck(const Deck &o);
    Card *draw();
    void remove(Card &card);
    void execute(Card &card);
};

ostream &operator<<(ostream &os, Deck &o);

#endif