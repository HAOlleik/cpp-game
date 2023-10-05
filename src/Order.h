#ifndef ORDER_H
#define ORDER_H
#include <iostream>
using std::ostream;

#include "Player.h"

// Not sure yet if it is usefull, can be removed
enum OrderType
{
	deploy,
	advance,
	bomb,
	blockade,
	airlift,
	negotiate
};

class Order
{
public:
	Order();
	Order(string* str);
	Order(const Order& o);
	void execute(Player& player);
	bool validate(string* player);
private:
	string* order;
};

class DeployOrder : public Order
{
};

class AdvanceOrder : public Order
{
};

class BombOrder : public Order
{
};

class BlockadeOrder : public Order
{
};

class AirliftOrder : public Order
{
};

class NegotiateOrder : public Order
{
};

// not sure if it should be defined for each of the order type. I thin not
ostream&
operator<<(ostream& os, Order& o);

#endif