#include "Player.h"
using namespace std;

// Default constructor
Player::Player()
{
	*name = "Player";
	*reinforcementPool = 0;
	vector<Territory *> territories;
	vector<Card *> cards;
	vector<Order *> orders;
}

// Parameter constructor
Player::Player(string *name)
{
	this->name = name;
}

// Parameter constructor
Player::Player(int *reinforcementPool, string *name, vector<Territory *> territories, vector<Card *> cards, vector<Order *> orders)
{
	this->reinforcementPool = reinforcementPool;
	this->name = name;
	this->territories = territories;
	this->cards = cards;
	this->orders = orders;
}

// Copy constructor
Player::Player(const Player &plr)
{
	this->reinforcementPool = plr.reinforcementPool;
	this->name = plr.name;
	this->territories = plr.territories;
	this->cards = plr.cards;
	this->orders = plr.orders;
}

// Operator assignment
Player &Player::operator=(const Player &p)
{
	this->reinforcementPool = p.reinforcementPool;
	this->name = p.name;
	this->territories = p.territories;
	this->cards = p.cards;
	this->orders = p.orders;
	return *this;
}

ostream &operator<<(ostream &os, const Player &player) // insertion stream operator
{
	os << "Name of the player: " << player.name << endl
	   << "ReinforcementPool: " << endl;
	return os;
}

// Destructor
Player::~Player()
{
	*name = "";
	name = nullptr;
	delete name;
	*reinforcementPool = 0;
	delete reinforcementPool;
	territories.clear();
	cards.clear();

	for (auto ord : orders)
	{
		delete ord;
	}
	orders.clear();
	vector<Territory *>().swap(territories);
	vector<Card *>().swap(cards);
	vector<Order *>().swap(orders);
}

// Get name of the palyer
string Player::getNamePlayer()
{
	return *name;
}

// Set name of the player
void Player::setNamePlayer(string *str)
{
	this->name = str;
}

// get Territories that are neighblors
int Player::getReinforcementPool()
{
	return *reinforcementPool;
}

// set army units
void Player::setReinforcementPool(int *pool)
{
	this->reinforcementPool = pool;
}

// get Territory
vector<Territory *> Player::getTerritories()
{
	return territories;
}

void Player::setTerritories(Territory &terr)
{
	this->territories.push_back(&terr);
}
// Get list of territories that are to be attacked
void Player::toAttack()
{
	for (size_t i = 0; i < territories.size(); i++)
	{
		cout << *territories[i] << endl;
	}
}

// Get list of territories that are to be defended
void Player::toDefend()
{
	for (size_t i = 0; i < territories.size(); i++)
	{
		cout << *territories[i] << endl;
	}
}

// Validates if the irder is correct
bool Player::validate(string *s)
{
	string temps = *s;
	if (temps == "deploy" || temps == "advance" || temps == "bomb" || temps == "blockade" || temps == "airlift" || temps == "negotiate")
	{
		return true;
	}
	return false;
}

// Creats list of order objects
void Player::issueOrder(string *ord)
{
	Order *ordObj = new Order(ord);
	if (validate(ord))
	{
		orders.push_back(ordObj);
		cout << *ord << endl;
	}
	else
		cout << "Wrong order!" << endl;
}