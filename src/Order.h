#pragma once
#include <iostream>
using std::ostream;
#include <queue>
using std::queue;

#include "LoggingObserver.h"
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

class Order : public ILoggable, public Subject
{
public:
    Order();
    Order(string *str);
    Order(const Order &o);            // copy contructor
    Order &operator=(const Order &c); // assignment operrator

    // Destructor
    virtual ~Order() = default;
    string stringToLog();

    string *orderName; // not sure if needed

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
    DeployOrder(const DeployOrder &d);                                       // copy

    
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
    AdvanceOrder(Player *player, Territory *sourceTerritory, Territory *targetTerritory, int nbOfArmies);
    virtual bool validate() override;
    virtual void execute() override;

    bool isValid;

private:
    Player *currentPlayer;
    Territory *source;
    Territory *target;
    int nbOfArmies;
    void attackSimilate(Territory *source, Territory *target, int nbOfArmies);
    Order *clone() const override;
};

class BombOrder : public Order
{
public:
    BombOrder();
    BombOrder(Player *currentPlayer, Territory *target);
    virtual bool validate() override;
    virtual void execute() override;

    bool isValid;

private:
    Player *currentPlayer;
    Territory *target;
    Order *clone() const override;
};

class BlockadeOrder : public Order
{
public:
    BlockadeOrder();
    BlockadeOrder(Player *player, Territory *target);
    virtual bool validate() override;
    virtual void execute() override;

    bool isValid;

private:
    Player *currentPlayer;
    Territory *target;
    Order *clone() const override;
};

class AirliftOrder : public Order
{
public:
    AirliftOrder();
    AirliftOrder(Player *player, Territory *sourceTerritory, Territory *targetTerritory, int nbOfArmies);
    virtual bool validate() override;
    virtual void execute() override;

    bool isValid;

private:
    Player *currentPlayer;
    Territory *source;
    Territory *target;
    int nbOfArmies;
    Order *clone() const override;
};

class NegotiateOrder : public Order
{
public:
    NegotiateOrder();
    NegotiateOrder(Player *currentPlayer, Player *targetPlayer);
    virtual bool validate() override;
    virtual void execute() override;

    bool isValid;

private:
    Player *currentPlayer;
    Player *targetPlayer;
    Order *clone() const override;
};

class OrdersList : public ILoggable, public Subject
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
    string stringToLog();
    void printOrders() const;
};

// not sure if it should be defined for each of the order type. I thin not
// ostream &
// operator<<(ostream &os, Order &o);
