#include <iostream>
using std::ostream;
#include <queue>
using std::queue;

// #include "Player.h"
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
    Order(string* str);
    Order(const Order &o); //copy contructor
    // void execute(Player &player);
    bool validate();
    string* orderName;
};
ostream &operator<<(ostream &os, const Order &o);

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
	void addOrder(Order *order);
	void printOrders() const;
};

// not sure if it should be defined for each of the order type. I thin not
// ostream &
// operator<<(ostream &os, Order &o);

//free function
void testOrdersLists();