#pragma once

#include "Order.h"

Order::Order() {}

Order::Order(string* str)
{
	this->orderName = str;
}

DeployOrder::DeployOrder() {
	cout << "Deploy Order Created" << endl;
	string d = "deploy";
	this->orderName = &d;
	this->isValid = true;

}
bool DeployOrder::validate() {
	return true;
}
void DeployOrder::execute() {
	if (this->isValid) {
		cout << "Deploy order executing" << endl;
	}
}


AdvanceOrder::AdvanceOrder() {
	cout << "Advance Order Created" << endl;
	string a = "advance";
	this->orderName = &a;
	this->isValid = true;
}
bool AdvanceOrder::validate()
{
	return true;
}
void AdvanceOrder::execute()
{
	if (this->isValid)
	{
		cout << "Advance order executing" << endl;
	}
}

BombOrder::BombOrder() {
	cout << "Bomb Order Created" << endl;
	// *orderName = "Bomb";
	string b = "Bomb";
	this->orderName = &b;
	this->isValid = true;
}
bool BombOrder::validate()
{
	return true;
}
void BombOrder::execute()
{
	if (this->isValid) {
		cout << "Bomb order executing" << endl;
	}
}

BlockadeOrder::BlockadeOrder() {
	cout << "Blockade Order Created" << endl;
	// *orderName = "Blockade";
	string bl = "blockade";
	this->orderName = &bl;
	this->isValid = true;
}
bool BlockadeOrder::validate()
{
	return true;
}
void BlockadeOrder::execute()
{
	if (this->isValid)
	{
		cout << "Blockade order executing" << endl;
	}
}

AirliftOrder::AirliftOrder() {
	cout << "Airlift Order Created" << endl;
	// *orderName = "Airlift";
	string o = "airlift";
	this->orderName = &o;
	this->isValid = true;
}
bool AirliftOrder::validate()
{
	return true;
}
void AirliftOrder::execute()
{
	if (this->isValid)
	{
		cout << "Airlift order executing" << endl;
	}
}

NegotiateOrder::NegotiateOrder() {
	cout << "Negotiate Order Created" << endl;
	string neg = "negotiate";
	this->orderName = &neg;
	this->isValid = true;
}
bool NegotiateOrder::validate()
{
	return true;
}
void NegotiateOrder::execute()
{
	if (this->isValid)
	{
		cout << "Negotiate order executing" << endl;
	}
}

ostream& operator<<(ostream& os, const Order& o)
{
	os << "Order Name: " << o.orderName; // Replace this with the actual output you want
	return os;
}

//methods for orderList
OrdersList::OrdersList() {}
void OrdersList::addOrder(Order* order) {
	this->_orders.push(order);
	cout << "done" << endl;
}
void OrdersList::move(int initialPosition, int desiredPosition)
{
	// Check if the initial and desired positions are valid
	if (initialPosition < 0 || initialPosition >= _orders.size() ||
		desiredPosition < 0 || desiredPosition >= _orders.size())
	{
		std::cerr << "Invalid move positions." << std::endl;
		return;
	}

	// Temporarily store the elements
	std::queue<Order*> tempQueue;
	int currentPos = 0;

	// Remove and save all elements from the queue until the initial position
	while (currentPos < initialPosition)
	{
		tempQueue.push(_orders.front());
		_orders.pop();
		currentPos++;
	}

	// Remove the element to be moved and save it
	Order* movedOrder = _orders.front();
	_orders.pop();

	// Skip the desired position, we will insert it later
	currentPos++;

	// Remove and save the rest of the elements from the queue
	while (currentPos < desiredPosition)
	{
		tempQueue.push(_orders.front());
		_orders.pop();
		currentPos++;
	}

	// Insert the moved element at the desired position
	_orders.push(movedOrder);

	// Insert the remaining elements back into the queue
	while (!tempQueue.empty())
	{
		_orders.push(tempQueue.front());
		tempQueue.pop();
	}
}

// Add this member function to your OrdersList class
void OrdersList::printOrders() const
{
	std::queue<Order*> tempQueue = _orders;

	while (!tempQueue.empty())
	{
		Order* order = tempQueue.front();
		tempQueue.pop();
		// Assuming you have an operator<< overload for Order objects
		std::cout << *order << std::endl;
	}
}

void OrdersList::remove(int index)
{
	// Check if the index is valid
	if (index < 0 || index >= _orders.size())
	{
		std::cerr << "Invalid index for removal." << std::endl;
		return;
	}

	// Temporarily store the elements
	std::queue<Order*> tempQueue;
	int currentPos = 0;

	// Remove and save all elements from the queue until the specified index
	while (currentPos < index)
	{
		tempQueue.push(_orders.front());
		_orders.pop();
		currentPos++;
	}

	// Remove the element at the specified index (do not save it)
	_orders.pop();

	// Insert the remaining elements back into the queue
	while (!tempQueue.empty())
	{
		_orders.push(tempQueue.front());
		tempQueue.pop();
	}
}
