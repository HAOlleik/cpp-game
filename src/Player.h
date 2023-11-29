#pragma once

#include <memory>
#include <string>
#include <iostream>
using std::ostream;
#include <vector>
using std::vector;
#include <set>
#include <time.h>
#include <algorithm>
#include <assert.h>
using namespace std;

#include "Territory.h"
#include "Continent.h"
class Map;
class GameEngine;
class Hand;
class Deck;
class Order;
class Card;
class DeployOrder;
class BombOrder;
class PlayerStrategy;
class OrdersList;
#include "Cards.h"
#include "Order.h"
#include "PlayerStrategies.h"

class Player
{
public:
	Player(); // default constructor
	Player(string *name);
	// Parameter constructor
	Player(int *reinforcementPool, string *name, vector<Territory *> territories, Hand *playerHand, list<Order *> orders);
	// Parameter constructor
	Player(int *reinforcementPool, string *name, vector<Territory *> territories, Hand *playerHand, list<Order *> orders, bool passTurn);
	// copy constructor
	Player(const Player &plr);
	// Operator assignment
	Player &operator=(const Player &p);
	// insertion stream operator
	friend ostream &operator<<(ostream &os, const Player &player);
	~Player();
	Player(PlayerStrategy*);

	// Get name of the palyer
	string getName();
	// Territories to be attacked
	vector<Territory *> toAttack();
	// Territories to be defended
	vector<Territory *> toDefend();
	// get Territory
	vector<Territory *> getTerritories();
	// get Territories that are neighblors
	vector<Territory *> getNeigbourTerritories();
	list<Order *> getOrders() const;
	bool getPassTurn();
	void setPassTurn(bool);
	Hand *getHand();
	OrdersList *getOrdersList();
	void addReinforcements(int);
	int getReinforcementPool();			  // get army units
	int continentBonusValue();			  // the player is given a number of army units corresponding to the continent’s control bonus value
	void setReinforcementPool(int pool);  // set army units
	void setTerritories(Territory *terr); // set Territory
	void setNamePlayer(string *str);	  // Set name of the player
										  // Players issue orders and place them in their order list through a call to the Player::issueOrder() method
										  // print orders from orderList
	void printOrder();
	// void printHandCard(); // prind hand card
	void issueOrder();
	// check if any of the users should be removed

	// Only for Assignment 1
	// bool validate(string *s);									// Only for Assignment 1
	void removeTerritory(Territory &territory);
	PlayerStrategy* getPlayerStrategy() const;
	void setPlayerStrategy(PlayerStrategy*);
	void setConqueredTerritory(bool i) { this->conqueredTerritory = i; };
	bool getConqueredTerritory() { return this->conqueredTerritory; };

private:
	int *reinforcementPool;
	string *name;
	vector<Territory *> territories;
	Hand *playerHand;
	list<Order *> orders; // WHOEVER WROTE THIS FIX IT TO USE OBJECT OrdersList
	OrdersList *orderList;
	std::shared_ptr<bool> passTurn = std::make_shared<bool>(false);
	vector<Card *> cards;
	PlayerStrategy *playerStrategy;
	bool conqueredTerritory = false;

	// Friend classes of the Player class
	friend class GameEngine;
	friend class Card;
	friend class Map;
	friend class Hand;
	friend class Order;
	friend class DeployOrder;
	friend class BombOrder;
};