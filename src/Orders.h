#ifndef ORDERS_H
#define ORDERS_H
#include <queue>
using std::queue;
#include <iostream>
using std::ostream;

#include "Order.h"

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

ostream &operator<<(ostream &os, OrdersList &o);

#endif