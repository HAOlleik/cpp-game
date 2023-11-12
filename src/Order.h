#pragma once
#include <iostream>
using std::ostream;
#include <queue>
using std::queue;

#include "Player.h"
using namespace std;

class Territory;
class Player;

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
    Order(string *str);
    Order(const Order &o);            // copy contructor
    Order &operator=(const Order &c); // assignment operrator

    // Destructor
    virtual ~Order() = default;

    string *orderName; //not sure if needed

    /* Pure virtual execute method */
    virtual bool validate() = 0;
    virtual void execute() = 0;

    virtual Order *clone() const = 0;

    // Stream insertion
    friend ostream &operator<<(ostream &os, const Order &order);

    // Access modifiers
    const string &getDescription() const;
    void setDescription(string &desc);

    const string &getEffect() const;
    void setEffect(string &effect);

    void setPlayer(Player *player);

protected:
    string *orderDescription;
    string *orderEffect;
    Player *player;
};
ostream &operator<<(ostream &os, const Order &o);

class DeployOrder : public Order
{
public:
    DeployOrder();
    DeployOrder(Player *player, Territory *targetTerritory, int nbOfArmies); // parameterized
    DeployOrder(const DeployOrder &d);               // copy

    /* Destructor */
    ~DeployOrder();

    
    void execute() override;
    bool validate() override;
    // bool isValid;

private:
    Player *currentPlayer;
    Territory *target;
    int nbOfArmies;
    Order *clone() const override;
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
    OrdersList(const OrdersList &o); // copy constuctor
    void move(int initialPosition, int desiredPosition);
    void remove(int index);
    void execute();
    void addOrder(Order *order);
    void printOrders() const;
};

// not sure if it should be defined for each of the order type. I thin not
// ostream &
// operator<<(ostream &os, Order &o);
