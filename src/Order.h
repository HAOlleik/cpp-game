#ifndef ORDER_H
#define ORDER_H
#include <iostream>
using std::ostream;
#include <queue>
using std::queue;

#include "Player.h"
using namespace std;

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
    Order(const Order &o); //copy contructor
    void execute(Player &player);
    bool validate();
    string* orderName;
};

class DeployOrder : public Order
{
public:
    DeployOrder();
    void execute();
    bool validate();
    bool isValid;
};

class AdvanceOrder : public Order
{
public:
    AdvanceOrder();
    void execute();
    bool validate();
    bool isValid;
};

class BombOrder : public Order
{
public:
    BombOrder();
    void execute();
    bool validate();
    bool isValid;
};

class BlockadeOrder : public Order
{
public:
    BlockadeOrder();
    void execute();
    bool validate();
    bool isValid;
};

class AirliftOrder : public Order
{
public:
    AirliftOrder();
    void execute();
    bool validate();
    bool isValid;
};

class NegotiateOrder : public Order
{
public:
    NegotiateOrder();
    void execute();
    bool validate();
    bool isValid;
};

class OrdersList
{
private:
    // FIFO queue
    queue<Order *> _orders;

public:
    OrdersList();
    OrdersList(const OrdersList &o);
    void move(int initialPosition, int desiredPosition);
    void remove(int index);
    void execute();
    void addOrder(Order *order)
    {
        _orders.push(order);
    }
};

// not sure if it should be defined for each of the order type. I thin not
ostream &
operator<<(ostream &os, Order &o);

#endif