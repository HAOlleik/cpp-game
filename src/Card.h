#ifndef CARD_H
#define CARD_H
#include <iostream>
using std::ostream;

// forward declaration
class Player;

class Card
{
private:
    Player *_player;

public:
    Card();
    Card(const Card &c);
    void play(Player &p);
    bool validate();
};

class BombCard : public Card
{
};

class ReinforcementCard : public Card
{
};

class BlockadeCard : public Card
{
};

class AirliftCard : public Card
{
};

class DiplomacyCard : public Card
{
};

ostream &
operator<<(ostream &os, Card &c);

#endif