#include "Player.h"

// Default constructor
Player::Player()
	: reinforcementPool(new int(0)), name(new string("Player")),
	  territories(vector<Territory *>()), playerHand(new Hand()), orders(vector<Order *>()) {}

// Parameter constructor
Player::Player(string *name) : reinforcementPool(new int(0)), name(name),
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
	delete name;
	delete reinforcementPool;

	for (auto ord : orders)
	{
		delete ord;
	}

	territories.clear();
	cards.clear();
	orders.clear();
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

void Player::addReinforcements(int n)
{
	*reinforcementPool += n;
}

// set army units
void Player::setReinforcementPool(int pool)
{
	*this->reinforcementPool = pool;
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
vector<Territory *> Player::getNeigbourTerritories()
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
vector<Territory *> Player::toAttack()
{
	vector<Territory *> listToAttack;
	listToAttack = getNeigbourTerritories();

	cout << "The list of territories that are be Attacked" << endl;
	for (uint64_t i = 0; i < listToAttack.size(); i++)
	{
		// cout << "Index " << i << " Name of the territory : " << (*listToAttack[i]).getName() << " Name of the continent: " << (*listToAttack[i]).getContinent() << endl;
	}
	return listToAttack;
}

// Get list of territories that are to be defended
vector<Territory *> Player::toDefend()
{
	// vector<Territory *> listToDefend;
	// Territory *temp = NULL;
	// cout << "The list of territories that are be defended" << endl;
	// for (uint64_t i = 0; i < territories.size(); i++)
	// {
	// 	cout << "Index " << i << " Name of the territory : " << (*territories[i]).getName() << " Name of the continent: " << (*territories[i]).getContinent() << endl;
	// 	temp = territories[i];
	// 	listToDefend.push_back(temp);
	// }
	// return listToDefend;

	return territories;
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
Hand *Player::getHand()
{
	return playerHand;
}

void Player::issueOrder()
{
	vector<Territory *> listToAttack;
	listToAttack = toAttack();
	vector<Territory *> listToDefend;
	listToDefend = toDefend();
	srand(time(NULL));

	// Deploy order until no armies left
	while (getReinforcementPool() > 0)
	{
		int army = getReinforcementPool();

		for (uint64_t i = 0; i < listToDefend.size(); i++)
		{
			int temp = (rand() + 1) % (army + 1);
			temp += listToDefend[i]->getArmies();
			listToDefend[i]->setArmies(temp);
			army -= temp; // Update army by subtracting temp

			setReinforcementPool(army);

			if (army <= 0)
			{
				listToDefend[i]->setArmies(temp + army); // Adjust armies if army is negative
				setReinforcementPool(0);
			}
		}
	}

	// Advance order

	// int actionNumber = rand() % listToAttack.size();

	// int enemy = listToAttack[actionNumber]->getArmies();

	// Using one of the cards in the hand to issue an order
	if (!playerHand->getPlayHand().empty())
	{
		// playerHand->play(1,)

		int i = 0;
		int j = 0;
		// Assuming you want to use the first card in the hand for simplicity
		Card *selectedCard = playerHand->getPlayHand().front();

		// Check the type of the card and issue a corresponding order
		if (selectedCard->getCardType() == "deploy")
		{
			// Create a deploy order and add it to the player's orders
			Territory *targetTerritory = listToAttack[i]; // Get the target territory
			orders.push_back(new DeployOrder(this, targetTerritory, 3));

			// Output order information (for demonstration purposes)
			std::cout << "Player " << getName() << " issued DEPLOY order." << std::endl;
			i++;
		}
		else if (selectedCard->getCardType() == "advance")
		{
			// Assuming source and target territories are obtained from Map vector
			Territory *sourceTerritory = listToDefend[j]; // Get the source territory
			Territory *targetTerritory = listToAttack[i]; // Get the target territory

			// Create an advance order and add it to the player's orders
			orders.push_back(new AdvanceOrder(this, sourceTerritory, targetTerritory, 3));

			// Output order information (for demonstration purposes)
			std::cout << "Player " << getName() << " issued ADVANCE order." << std::endl;
			i++;
			j++;
		}
		else if (selectedCard->getCardType() == "airlift")
		{
			// Assuming target territory is obtained from Map vector
			Territory *sourceTerritory = listToDefend[j]; // Get the source territory
			Territory *targetTerritory = listToAttack[i]; // Get the target territory

			// Create a bomb order and add it to the player's orders
			orders.push_back(new AirliftOrder(this, sourceTerritory, targetTerritory, 3));

			// Output order information (for demonstration purposes)
			std::cout << "Player " << getName() << " issued AIRLIFT order." << std::endl;
			i++;
			j++;
		}
		else if (selectedCard->getCardType() == "bomb")
		{
			// Assuming target territory is obtained from Map vector
			Territory *targetTerritory = listToAttack[i]; // Get the target territory

			// Create a bomb order and add it to the player's orders
			orders.push_back(new BombOrder(this, targetTerritory));

			// Output order information (for demonstration purposes)
			std::cout << "Player " << getName() << " issued BOMB order." << std::endl;
			i++;
		}
		else if (selectedCard->getCardType() == "blockade")
		{
			// Assuming target territory is obtained from Map vector
			Territory *targetTerritory = listToAttack[i]; // Get the target territory

			// Create a bomb order and add it to the player's orders
			orders.push_back(new BlockadeOrder(this, targetTerritory));

			// Output order information (for demonstration purposes)
			std::cout << "Player " << getName() << " issued BLOCKADE order." << std::endl;
			i++;
		}
		else if (selectedCard->getCardType() == "diplomacy")
		{
			// Assuming target territory is obtained from Map vector
			Territory *targetTerritory = listToAttack[i]; // Get the target territory

			// Create a bomb order and add it to the player's orders
			orders.push_back(new NegotiateOrder(this, targetTerritory->getOwner().get()));

			// Output order information (for demonstration purposes)
			std::cout << "Player " << getName() << " issued NEGOTIATE order." << std::endl;
			i++;
		}

		// Remove the used card from the hand
		playerHand->getPlayHand().erase(playerHand->getPlayHand().begin());
	}

	// Continue with the rest of the order issuance logic
	// ...
}

void Player::removeTerritory(Territory &territory)
{
	territory.setOwner(nullptr);
	auto end = territories.end();
	for (auto it = territories.begin(); it != end; it++)
	{
		if (territory.getName() == (*it)->getName())
		{
			territories.erase(it);
			return;
		}
	}
	throw std::runtime_error("Territory wasn't in the player's list.");
}

vector<Order *> Player::getOrders() const
{
	return orders;
}

void Player::printOrder()
{
	for (uint64_t i = 0; i < orders.size(); i++)
	{
		cout << "<" << orders.at(i) << "> ";
	}
	cout << endl;
}