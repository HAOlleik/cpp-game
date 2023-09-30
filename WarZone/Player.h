#pragma once
#include <iostream>
using std::ostream;
#include <vector>
using std::vector;

#include "Cards.h"
#include "Orders.h"
#include "Territory.h"

class Player
{
private:
    vector<Territory*> _territories;
    vector<Cards*> _cards;
    vector<Orders*> _orders;

public:
    Player();
    Player(const Player& p);
    vector<Territory*> toDefend();
    vector<Territory*> toAttack();
    void issueOrder(const OrderType& orderType);

    // needs access to validate
    friend bool Cards::validate();
    friend void Orders::execute(Player& player);
    friend bool Orders::validate(Player& player);
};

ostream& operator<<(ostream& os, Player& p);

