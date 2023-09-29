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
    void move();
    void remove();
    void execute();
};

ostream &operator<<(ostream &os, OrdersList &o);

#endif