#pragma once

#include "Player.h"
using namespace std;

// Default constructor
Player::Player()
{
	*name = "Player";
	vector<string*>territories;
	vector<string*>cards;
	vector<Order*>orders;
}

// Parameter constructor
Player::Player(string* name)
{
	this->name = name;
}

// Parameter constructor
Player::Player(string* name, vector<string*>territories, vector<string*>cards, vector<Order*>orders)
{
	this->name = name;
	this->territories = territories;
	this->cards = cards;
	this->orders = orders;
}

// Copy constructor
Player::Player(const Player& plr)
{
	this->name = plr.name;
	this->territories = plr.territories;
	this->cards = plr.cards;
	this->orders = plr.orders;
}

// Operator assignment
Player& Player::operator=(const Player& p)
{
	this->name = p.name;
	this->territories = p.territories;
	this->cards = p.cards;
	this->orders = p.orders;
	return *this;
}

ostream& operator<<(ostream& os, const Player& player)	//insertion stream operator
{
	os << "Name of the player: " << player.name << endl;
	return os;
}

// Destructor
Player::~Player()
{
	*name = "";
	name = nullptr;
	delete name;
	territories.clear();
	cards.clear();

	//for (auto ord : orders)
	//{
	//	delete ord;
	//}
	orders.clear();
	//vector<Territory*>().swap(territories);
	//vector<string*>().swap(cards);
	vector<Order*>().swap(orders);
}

// Get name of the palyer
string Player::getName()
{
	return *name;
}

// Set name of the player
void Player::setName(string* str)
{
	this->name = str;
}

// Get list of territories that are to be attacked
void Player::toAttack()
{
	for (int i = 0; i < territories.size(); i++)
	{
		cout << *territories[i] << endl;
	}
}

// Get list of territories that are to be defended
void Player::toDefend()
{
	for (int i = 0; i < territories.size(); i++)
	{
		cout << *territories[i] << endl;
	}
}

// Validates if the irder is correct
bool validate(string* s)
{
	string temps = *s;
	if (temps == "deploy" || temps == "advance" || temps == "bomb" || temps == "blockade"
		|| temps == "airlift" || temps == "negotiate")
		return true;
}

// Creats list of order objects
void Player::issueOrder(string* ord)
{
	Order* ordObj = new Order(ord);
	if (validate(ord))
	{
		orders.push_back(ordObj);
		cout << ord << endl;
	}
	else
		cout << "Wrong order!" << endl;

}