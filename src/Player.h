#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
using std::ostream;
#include <vector>
using std::vector;

#include "Card.h"
#include "Order.h"
#include "Territory.h"

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
    void issueOrder(const OrderType &orderType);

    // needs access to validate
    friend bool Card::validate();
    friend void Order::execute(Player &player);
    friend bool Order::validate(Player &player);
};

ostream &operator<<(ostream &os, Player &p);

#endif