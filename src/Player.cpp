#include "Player.h"
#include <set>
#include <time.h>
#include <algorithm>
#include <assert.h>
using namespace std;

// Default constructor
Player::Player()
	: name(new string("Player")), reinforcementPool(new int(0)),
	  territories(vector<Territory *>()), playerHand(new Hand()), orders(vector<Order *>()) {}

// Parameter constructor
Player::Player(string *name) : name(name), reinforcementPool(new int(0)),
							   territories(vector<Territory *>()), playerHand(new Hand()), orders(vector<Order *>()) {}

// Parameter constructor
Player::Player(int *reinforcementPool, string *name, vector<Territory *> territories, Hand *playerHand, vector<Order *> orders)
{
	this->reinforcementPool = reinforcementPool;
	this->name = name;
	this->territories = territories;
	this->playerHand = playerHand;
	this->orders = orders;
}

// Copy constructor
Player::Player(const Player &plr)
{
	this->reinforcementPool = plr.reinforcementPool;
	this->name = plr.name;
	this->territories = plr.territories;
	this->playerHand = new Hand(*(plr.playerHand));
	this->orders = plr.orders;
}

// Operator assignment
Player &Player::operator=(const Player &p)
{
	if (this != &p)
	{ // self-assignment check
		delete name;
		delete reinforcementPool;
		delete playerHand;
		name = new string(*p.name);
		reinforcementPool = new int(*p.reinforcementPool);
		territories = p.territories;
		playerHand = new Hand(*(p.playerHand));
		orders = p.orders;
	}
	return *this;
}

ostream &operator<<(ostream &os, const Player &player) // insertion stream operator
{
	os << "Name of the player: " << player.name << endl
	   << "ReinforcementPool: " << endl
	   << "Player's Hand: " << *(player.playerHand) << endl;
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
string Player::getName()
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

// get Territories that are neighblors
vector<Territory *> Player::getNeigbourTerritories(vector<Territory *> Map)
{
	vector<Territory *> neighbTerrritories;
	for (auto &t : territories)
	{
		// for all territories that player owns, get adjecent and
		// add to the set
		for (auto &tt : t->getAdjacentTerritories())
			neighbTerrritories.push_back(tt.get()); // using get to get raw pointer from smart pointers
	}

	return neighbTerrritories;
}

// Get list of territories that are to be attacked
vector<Territory *> Player::toAttack(vector<Territory *> Map)
{
	vector<Territory *> listToAttack;
	listToAttack = getNeigbourTerritories(Map);

	cout << "The list of territories that are be Attacked" << endl;
	for (int i = 0; i < listToAttack.size(); i++)
	{
		cout << "Index " << i << " Name of the territory : " << (*listToAttack[i]).getName() << " Name of the continent: " << (*listToAttack[i]).getContinent() << endl;
	}
	return listToAttack;
}

// Get list of territories that are to be defended
vector<Territory *> Player::toDefend()
{
	vector<Territory *> listToDefend;
	Territory *temp = NULL;
	cout << "The list of territories that are be defended" << endl;
	for (int i = 0; i < territories.size(); i++)
	{
		cout << "Index " << i << " Name of the territory : " << (*territories[i]).getName() << " Name of the continent: " << (*territories[i]).getContinent() << endl;
		temp = territories[i];
		listToDefend.push_back(temp);
	}
	return listToDefend;
}

// the player is given a number of army units corresponding to the continent’s control bonus value
// bool Player::continentBonusValue()
// {
// 	string a = "NA";
// 	//Continent *conA = new Continent(a);
// 	string b = "AS";
// 	//Continent *conB = new Continent(b);
// 	string c = "SA";
// 	//Continent *conC = new Continent(c);
// 	string d = "AU";
// 	//Continent *conD = new Continent(d);
// 	string e = "EU";
// 	//Continent *conE = new Continent(e);
// 	string f = "AF";
// 	//Continent *conF = new Continent(f);
// 	int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0;
// 	for (int i = 0; i < territories.size(); i++)
// 	{
// 		if ((*territories[i]).getContinent().get()->getName().compare(a))
// 		{
// 			c1++;
// 		}
// 		if ((*territories[i]).getContinent().get()->getName().compare(b))
// 		{
// 			c2++;
// 		}
// 		if ((*territories[i]).getContinent().get()->getName().compare(c))
// 		{
// 			c3++;
// 		}
// 		if ((*territories[i]).getContinent().get()->getName().compare(d))
// 		{
// 			c4++;
// 		}
// 		if ((*territories[i]).getContinent().get()->getName().compare(e))
// 		{
// 			c5++;
// 		}
// 		if ((*territories[i]).getContinent().get()->getName().compare(f))
// 		{
// 			c6++;
// 		}
// 	}
// 	if (c1 == 3)
// 	{
// 		return true;
// 	} // NA
// 	if (c2 == 3)
// 	{
// 		return true;
// 	} // AS
// 	if (c3 == 1)
// 	{
// 		return true;
// 	} // SA
// 	if (c4 == 1)
// 	{
// 		return true;
// 	} // AU
// 	if (c5 == 1)
// 	{
// 		return true;
// 	} // EU
// 	if (c6 == 1)
// 	{
// 		return true;
// 	} // EU

// 	return false;
// }

bool Player::continentBonusValue()
{
	// get first continent to check
	std::vector<Territory *> notMatched;
	for (auto &t : territories)
	{
		// if found in notMatched, means already checked, skip
		if (std::find(notMatched.begin(), notMatched.end(), t) != notMatched.end())
		{
			continue;
		}

		// get current continent
		std::shared_ptr<Continent> current = t->getContinent();
		std::vector<Territory *> matches;
		// copy into matches all terr if their continent is == to current
		std::copy_if(territories.begin(), territories.end(), std::back_inserter(matches), [&](Territory *v)
					 { return v->getContinent() == current; });

		// if the size of matches == to current continent terr size good
		if (matches.size() == current->getTerritories().size())
		{
			reinforcementPool += current->getScore();
			return true;
		}
		else
		{
			// if not add all terr from current iter to notMatched
			notMatched.insert(notMatched.end(), matches.begin(), matches.end());
			return false;
		}
	}
}

// Only for Assignment 1
// Validates if the irder is correct
// bool Player::validate(string *s)
// {
// 	string temps = *s;
// 	if (temps == "deploy" || temps == "advance" || temps == "bomb" || temps == "blockade" || temps == "airlift" || temps == "negotiate")
// 	{
// 		return true;
// 	}
// 	return false;
// }

// get hand of cards for player
Hand Player::getHand()
{
	return *playerHand;
}

void Player::issueOrder(vector<Territory *> Map)
{
	vector<Territory *> listToAttack;
	listToAttack = toAttack(Map);
	vector<Territory *> listToDefend;
	listToDefend = toDefend();

	// Deploy order until no armies left
	while (getReinforcementPool() != 0)
	{
		int army = getReinforcementPool();

		for (int i = 0; i < listToDefend.size(); i++)
		{
			srand(time(NULL));
			int temp = rand() % army + 1;
			temp += listToDefend[i]->getArmies();
			listToDefend[i]->setArmies(temp);
			army = temp - army;
			int *armPoint = &army;
			setReinforcementPool(armPoint);
			if (army == 1)
			{
				temp = 1;
				temp += listToDefend[i]->getArmies();
				listToDefend[i]->setArmies(temp);
				setReinforcementPool(0);
			}
		}
	}

	// Advance order
	srand(time(NULL));
	int actionNumber = rand() % listToAttack.size();

	int enemy = listToAttack[actionNumber]->getArmies();
}
