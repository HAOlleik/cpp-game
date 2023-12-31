#pragma once

#include <string>
#include <iostream>
using std::ostream;
#include <vector>
using std::vector;
using namespace std;

#include "Cards.h"
#include "Order.h"
#include "Territory.h"

class Player
{
public:
	Player();	// default constructor
	Player(string* name);
	Player(string* name, vector<string*>territories, vector<string*>cards, vector<Order*>orders);	// Parameter constructor
	Player(const Player& plr);	// copy constructor
	Player& operator=(const Player& p);	// Operator assignment
	friend ostream& operator<<(ostream& os, const Player& player); //insertion stream operator
	~Player();

	string getName();	// Get name of the palyer
	void toDefend();
	void toAttack();
	void setName(string* str);	// Set name of the player
	void issueOrder(string* str);

	bool validate(string* s);

private:
	string* name;
	vector<string*> territories;
	vector<string*> cards;
	vector<Order*> orders;
};