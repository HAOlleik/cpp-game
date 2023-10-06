#ifndef ORDER_H
#define ORDER_H
#include <iostream>
using std::ostream;

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
    Order(string *orderName);
    Order(const Order &o); //copy contructor
    void execute(Player &player);
    bool validate();
    string* orderName;
};

class DeployOrder : public Order
{
public:
    DeployOrder();
    DeployOrder(string* orderName);
    void execute();
    bool validate();
};

class AdvanceOrder : public Order
{
public:
    AdvanceOrder();
    AdvanceOrder(string* orderName);
    void execute();
    bool validate();
};

class BombOrder : public Order
{
public:
    BombOrder();
    BombOrder(string* orderName);
    void execute();
    bool validate();
};

class BlockadeOrder : public Order
{
public:
    BlockadeOrder();
    BlockadeOrder(string* orderName);
    void execute();
    bool validate();
};

class AirliftOrder : public Order
{
public:
    AirliftOrder();
    AirliftOrder(string* orderName);
    void execute();
    bool validate();
};

class NegotiateOrder : public Order
{
public:
    NegotiateOrder();
    NegotiateOrder(string* orderName);
    void execute();
    bool validate();
};

// not sure if it should be defined for each of the order type. I thin not
ostream &
operator<<(ostream &os, Order &o);

#endif