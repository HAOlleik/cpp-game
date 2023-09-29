#ifndef ORDER_H
#define ORDER_H
#include <iostream>
using std::ostream;

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
    Order(const Order &o);
    void execute();
    bool validate();
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
ostream &
operator<<(ostream &os, Order &o);

#endif