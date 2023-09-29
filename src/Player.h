#include <iostream>
using std::ostream;
#include <vector>
using std::vector;

#include "Territory.h"
#include "Order.h"

// forward reference to avoid circular inclusion problem
class Card
{
};

class Player
{
private:
    vector<Territory *> _territories;
    vector<Card *> _cards;
    vector<Order *> _orders;

public:
    Player();
    Player(const Player &p);
    vector<Territory *> toDefend();
    vector<Territory *> toAttack();
    void issueOrder();
};

ostream &operator<<(ostream &os, Player &p);
