#include "Order.h"

string deploy1 = "deploy";
string advance1 = "advance";
string bomb1 = "bomb";
string blockade1 = "blockade";
string airlift1 = "airlift";
string negotiate1 = "negotiate";

Order::Order() {}

Order::Order(string *str)
{
	this->orderName = str;
}
Order::Order(const Order &o)
{
	// Perform a deep copy of the orderName
	if (o.orderName != nullptr)
	{
		orderName = new string(*(o.orderName));
	}
	else
	{
		orderName = nullptr;
	}
}

Order &Order::operator=(const Order &other)
{

	if (this == &other)
	{
		return *this; // Return a reference to the current object
	}

	// Assign the orderName (assuming it's a pointer to a string)
	if (orderName != nullptr)
	{
		delete orderName; // Release existing resources
	}
	if (other.orderName != nullptr)
	{
		orderName = new string(*(other.orderName)); // Deep copy the string
	}
	else
	{
		orderName = nullptr;
	}

	// Return a reference to the current object
	return *this;
}

string Order::stringToLog()
{
	string returnString = "Order " + *orderName + " was executed.";
	return returnString;
}

DeployOrder::DeployOrder()
{
	cout << "Deploy Order Created" << endl;
	this->orderName = &deploy1;
	// this->isValid = true;
}

Order *DeployOrder::clone() const { return new DeployOrder(*this); }

DeployOrder::DeployOrder(Player *player, Territory *targetTerritory, int nbOfArmies)
{
	string name = "Deploy";
	this->setDescription(name);
	string orderEffect = "Deploys the troops";
	this->setEffect(orderEffect);

	this->currentPlayer = new Player(*player);
	this->target = new Territory(*targetTerritory);
	this->nbOfArmies = nbOfArmies;
}
bool DeployOrder::validate()
{
	if (target->getOwner()->getName() != currentPlayer->getName())
	{
		cout << "Invalid Order, target does not belong to current player" << endl;
		return false;
	}
	else if (nbOfArmies > currentPlayer->getReinforcementPool())
	{
		cout << currentPlayer->getReinforcementPool() << endl;
		cout << "Not enough armies in the reinforcement pool" << endl;
		return false;
	}
	else if (nbOfArmies < 1)
	{
		cout << "Please enter at least 1 army to deploy" << endl;
		return false;
	}
	else
	{
		cout << "Validated Deploy" << endl;
		return true;
	}
}

void DeployOrder::execute()
{
	if (this->validate())
	{
		target->setArmies(target->getArmies() + nbOfArmies);

		// Pass the address of the int value
		int newReinforcementPool = currentPlayer->getReinforcementPool() - nbOfArmies;
		currentPlayer->setReinforcementPool(&newReinforcementPool);

		cout << "Deploy has been executed" << endl;
	}
}

// Advance

Order *AdvanceOrder::clone() const { return new AdvanceOrder(*this); }

AdvanceOrder::AdvanceOrder()
{
	cout << "Advance Order Created" << endl;
	this->orderName = &advance1;
	this->isValid = true;
}

AdvanceOrder::AdvanceOrder(Player *player, Territory *sourceTerritory, Territory *targetTerritory, int nbOfArmies)
{
	string name = "Advance";
	this->setDescription(name);
	string orderEffect = "Advance Order";
	this->setEffect(orderEffect);

	this->currentPlayer = player;
	this->target = targetTerritory;
	this->source = sourceTerritory;
	this->nbOfArmies = nbOfArmies;
}

bool AdvanceOrder::validate()
{
	if (source->getOwner()->getName() != currentPlayer->getName())
	{
		cout << "Order is invalid" << endl;
		return false;
	}

	auto it = std::find(source->getAdjacentTerritories().begin(), source->getAdjacentTerritories().end(), target);
	if (it == source->getAdjacentTerritories().end())
	{
		cout << "The target territory is not adjacent to the source territory!\n"
			 << endl;
		return false;
	}

	else
	{
		cout << "Validated Advance" << endl;
		return true;
	}
}

void AdvanceOrder::attackSimilate(Territory *source, Territory *target, int numArmiesToMove)
{
	// Calculate the number of attacking and defending armies
	int numAttackingArmies = numArmiesToMove;
	int numDefendingArmies = target->getArmies();

	// Set random seed for battle simulation
	srand(static_cast<unsigned int>(time(nullptr)));

	// Simulate the battle
	while (numAttackingArmies > 0 && numDefendingArmies > 0)
	{
		if (rand() % 100 < 60)
		{
			--numDefendingArmies;
		}
		else if (rand() % 100 < 70)
		{
			--numAttackingArmies;
		}
	}

	// Determine the result of the battle
	if (numDefendingArmies <= 0)
	{
		// The attacker wins the battle and captures the territory
		cout << currentPlayer->getName() << " has conquered territory " << target->getName()
			 << " from " << target->getOwner()->getName() << endl;

		target->getOwner()->removeTerritory(*target);
		// capture the territory

		target->setArmies(numArmiesToMove);
		source->setArmies(std::max(0, source->getArmies() - numArmiesToMove));
	}
	else
	{
		// The defender wins the battle
		source->setArmies(std::max(0, source->getArmies() - numArmiesToMove));
	}
}

void AdvanceOrder::execute()
{
	if (this->validate())
	{

		if (source->getOwner()->getName() == target->getOwner()->getName())
		{
			int armiesToMove = nbOfArmies;

			// Check if the source has fewer armies than we're trying to move
			if (armiesToMove > source->getArmies())
			{
				armiesToMove = source->getArmies();
			}

			// Move the armies
			target->setArmies(target->getArmies() + armiesToMove);
			source->setArmies(source->getArmies() - armiesToMove);
		}

		else
		{

			attackSimilate(source, target, nbOfArmies);
			cout << "Advance has been executed" << endl;
		}
	}
}

// Bomb
Order *BombOrder::clone() const { return new BombOrder(*this); }

BombOrder::BombOrder()
{
	cout << "Bomb Order Created" << endl;
	// *orderName = "Bomb";
	this->orderName = &bomb1;
	this->isValid = true;
}
BombOrder::BombOrder(Player *currentPlayer, Territory *target)
{
	string name = "Bomb";
	this->setDescription(name);
	string orderEffect = "Bomb Order";
	this->setEffect(orderEffect);

	this->target = target;
	this->currentPlayer = currentPlayer;
}

bool BombOrder::validate()
{

	if (target->getOwner()->getName() == currentPlayer->getName())
	{
		cout << "target is current player territory" << endl;
		return false;
	}

	bool isAdjacent = 0;

	// check if the target is not adjacent to any of the current players territories
	for (Territory *territoryPtr : currentPlayer->getTerritories())
	{
		auto it = std::find(territoryPtr->getAdjacentTerritories().begin(), territoryPtr->getAdjacentTerritories().end(), target);
		if (!(it == territoryPtr->getAdjacentTerritories().end()))
		{
			isAdjacent = 1;
		}
	}

	if (!isAdjacent)
	{
		cout << "target is not adjacent to any of the current player's territories" << endl;
		return false;
	}

	else
	{
		cout << "Bomb has been validated" << endl;
		return true;
	}
}

void BombOrder::execute()
{
	if (this->validate())
	{
		target->setArmies((target->getArmies()) / 2);

		if (target->getArmies() == 0)
		{
			if (target->getOwner())
			{
				target->getOwner()->removeTerritory(*target);
			}
			target->setOwner(nullptr);
		}
		cout << "Bomb has been executed" << endl;
	}
}

// Blockade
Order *BlockadeOrder::clone() const { return new BlockadeOrder(*this); }

BlockadeOrder::BlockadeOrder()
{
	cout << "Blockade Order Created" << endl;
	// *orderName = "Blockade";
	this->orderName = &blockade1;
	this->isValid = true;
}
BlockadeOrder::BlockadeOrder(Player *player, Territory *target)
{
	string name = "Blockade";
	this->setDescription(name);
	string orderEffect = "Blocked Order";
	this->setEffect(orderEffect);

	this->currentPlayer = new Player(*player);
	this->target = new Territory(*target);
}

bool BlockadeOrder::validate()
{
	if (target->getOwner()->getName() != currentPlayer->getName())
	{
		cout << "Not your own territory!" << endl;
		return false;
	}
	else
	{
		cout << "Validated Blockade" << endl;
		return true;
	}
}

void BlockadeOrder::execute()
{
	if (this->validate())
	{
		target->setArmies(target->getArmies() * 2);
		if (target->getOwner())
		{
			target->getOwner()->removeTerritory(*target);
		}
		target->setOwner(nullptr); // Transfer to neutral
		cout << "Blockade has finished executing!\n"
			 << endl;
	}
}

// Airlift
Order *AirliftOrder::clone() const { return new AirliftOrder(*this); }
AirliftOrder::AirliftOrder()
{
	cout << "Airlift Order Created" << endl;
	// *orderName = "Airlift";
	this->orderName = &airlift1;
	this->isValid = true;
}
AirliftOrder::AirliftOrder(Player *player, Territory *sourceTerritory, Territory *targetTerritory, int nbOfArmies)
{
	string name = "Airlift";
	this->setDescription(name);
	string orderEffect = "Airlift Order";
	this->setEffect(orderEffect);

	this->currentPlayer = new Player(*player);
	this->source = new Territory(*sourceTerritory);
	this->target = new Territory(*targetTerritory);
	this->nbOfArmies = nbOfArmies;
}

bool AirliftOrder::validate()
{
	if (source->getOwner()->getName() != currentPlayer->getName() && target->getOwner()->getName() != currentPlayer->getName())
	{
		cout << "src or target does not belong to current player. order invalid" << endl;
		return false;
	}
	else
	{
		cout << "Validated Airlift" << endl;
		return true;
	}
}

void AirliftOrder::execute()
{
	if (this->validate())
	{
		source->setArmies(source->getArmies() - nbOfArmies);
		target->setArmies(target->getArmies() + nbOfArmies);
	}
	cout << "Airlift has been executed" << endl;
}

// Negotiate
Order *NegotiateOrder::clone() const { return new NegotiateOrder(*this); }
NegotiateOrder::NegotiateOrder()
{
	cout << "Negotiate Order Created" << endl;
	this->orderName = &negotiate1;
	this->isValid = true;
}
NegotiateOrder::NegotiateOrder(Player *currentPlayer, Player *targetPlayer)
{
	string name = "Negotiate";
	this->setDescription(name);
	string orderEffect = "Negotiate Order";
	this->setEffect(orderEffect);

	this->currentPlayer = currentPlayer;
	this->targetPlayer = targetPlayer;
}
bool NegotiateOrder::validate()
{

	if (targetPlayer == currentPlayer)
	{
		cout << "Target territory belongs to the current player, invalid order" << endl;
		return false;
	}
	else
	{
		cout << "Validated Negotiate" << endl;
		return true;
	}
}

void NegotiateOrder::execute()
{
	if (this->validate())
	{
		// currentPlayer->addFriend(targetPlayer);
		// targetPlayer->addFriend(currentPlayer);
	}
	cout << "Negotiation has been executed" << endl;
}

ostream &operator<<(ostream &os, const Order &o)
{
	os << "Order Name: " << *o.orderName; // Replace this with the actual output you want
	return os;
}

// methods for orderList
OrdersList::OrdersList() {}
void OrdersList::addOrder(Order *order)
{
	this->_orders.push(order);
	notify(this);
}
void OrdersList::move(int initialPosition, int desiredPosition)
{
	// Check if the initial and desired positions are valid
	if (initialPosition < 0 || initialPosition >= static_cast<int>(_orders.size()) ||
		desiredPosition < 0 || desiredPosition >= static_cast<int>(_orders.size()))
	{
		std::cerr << "Invalid move positions." << std::endl;
		return;
	}

	// Temporarily store the elements
	std::queue<Order *> tempQueue;
	int currentPos = 0;

	// Remove and save all elements from the queue until the initial position
	while (currentPos < initialPosition)
	{
		tempQueue.push(_orders.front());
		_orders.pop();
		currentPos++;
	}

	// Remove the element to be moved and save it
	Order *movedOrder = _orders.front();
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
	std::queue<Order *> tempQueue = _orders;

	while (!tempQueue.empty())
	{
		Order *order = tempQueue.front();
		tempQueue.pop();
		// Assuming you have an operator<< overload for Order objects
		std::cout << *order << std::endl;
	}
}

void OrdersList::remove(int index)
{
	// Check if the index is valid
	if (index < 0 || index >= static_cast<int>(_orders.size()))
	{
		std::cerr << "Invalid index for removal." << std::endl;
		return;
	}

	// Temporarily store the elements
	std::queue<Order *> tempQueue;
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

string OrdersList::stringToLog()
{
	if (!_orders.empty())
	{
		Order *lastOrder = _orders.back(); // Fetching the last order in the queue
		if (lastOrder != nullptr)
		{
			return "Order Issued: A " + *lastOrder->orderName + " order has been issued by Player.";
		}
	}
	return "No orders available."; // Or any default message for no orders in the queue
}