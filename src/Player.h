#pragma once

#include <string>
#include <iostream>
//using std::ostream;
#include <vector>
using std::vector;
using namespace std;

#include "Card.h"
#include "Order.h"
#include "Territory.h"

void testPlayers();

class Player
{
public:
	Player();	// default constructor
	Player(string* name);
	Player(string* name, vector<string*>territories, vector<string*>cards, vector<Order*>orders);	// Parameter constructor
	Player(const Player& plr);	// copy constructor
	Player& operator=(const Player& p);	// Operator assignment
	~Player();

	string getName();	// Get name of the palyer
	void toDefend();
	void toAttack();
	void setName(string* str);	// Set name of the player
	void issueOrder(string* str);

	// needs access to validate
	/*friend bool Card::validate();
	friend void Order::execute(Player& player);*/
	//friend bool Order::validate(string* player);

private:
	string* name;
	vector<string*> territories;
	vector<string*> cards;
	vector<Order*> orders;
};