#pragma once

#include <memory>
#include <string>
#include <iostream>
using std::ostream;
#include <vector>
using std::vector;
using namespace std;

#include "Cards.h"
#include "Order.h"
#include "Territory.h"
#include "GameEngine.h"
#include "Map.h"
#include "Continent.h"

class Player
{
public:
	Player(); // default constructor
	Player(string *name);
	Player(int *reinforcementPool, string *name, vector<Territory *> territories, vector<Card *> cards, vector<Order *> orders); // Parameter constructor
	Player(const Player &plr);																									 // copy constructor
	Player &operator=(const Player &p);																							 // Operator assignment
	friend ostream &operator<<(ostream &os, const Player &player);																 // insertion stream operator
	~Player();

	string getName();												 // Get name of the palyer
	vector<Territory *> toAttack(vector<Territory *>);				 // Territories to be attacked
	vector<Territory *> toDefend();									 // Territories to be defended
	vector<Territory *> getTerritories();							 // get Territory
	vector<Territory *> getNeigbourTerritories(vector<Territory *>); // get Territories that are neighblors
	// vector<Order *> getOrderList();									 // get a list of orders
	int getReinforcementPool();			  // get army units
	bool continentBonusValue();			  // the player is given a number of army units corresponding to the continent’s control bonus value
	void setReinforcementPool(int *pool); // set army units
	void setTerritories(Territory &terr); // set Territory
	void setNamePlayer(string *str);	  // Set name of the player
	void issueOrder(vector<Territory *>); // Players issue orders and place them in their order list through a call to the Player::issueOrder() method
										  // void printOrder();												 // print orders from orderList
										  // void printHandCard(); // prind hand card

	// bool validate(string *s);									// Only for Assignment 1
	void removeTerritory(Territory &territory);

private:
	string *name;
	int *reinforcementPool;

	vector<Card *> cards;
	vector<Territory *> territories;
	vector<Order *> orders;

	// Friend classes of the Player class
	friend class GameEngine;
	friend class Card;
	friend class Map;
};