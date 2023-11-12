#include "Player.h"

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

// Parameter constructor
Player::Player(int *reinforcementPool, string *name, vector<Territory *> territories, Hand *playerHand, vector<Order *> orders, bool passTurn)
{
	this->reinforcementPool = reinforcementPool;
	this->name = name;
	this->territories = territories;
	this->playerHand = playerHand;
	this->orders = orders;
	this->passTurn = std::make_shared<bool>(passTurn);
}

// Copy constructor
Player::Player(const Player &plr)
{
	this->reinforcementPool = plr.reinforcementPool;
	this->name = plr.name;
	this->territories = plr.territories;
	this->playerHand = new Hand(*(plr.playerHand));
	this->orders = plr.orders;
	this->passTurn = std::make_shared<bool>(plr.passTurn);
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
		passTurn = std::make_shared<bool>(p.passTurn);
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

bool Player::getPassTurn()
{
	return *passTurn;
}

void Player::setPassTurn(bool change)
{
	*passTurn = change;
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

void Player::setTerritories(Territory *terr)
{
	this->territories.push_back(terr);
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

int Player::continentBonusValue()
{
	// get first continent to check
	std::vector<Territory *> notMatched;
	int bonusPool = 0;
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
			bonusPool += current->getScore();
		}
		else
		{
			// if not add all terr from current iter to notMatched
			notMatched.insert(notMatched.end(), matches.begin(), matches.end());
		}
	}

	return bonusPool;
}

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
