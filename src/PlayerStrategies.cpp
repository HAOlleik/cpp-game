#include "PlayerStrategies.h"

bool compareTerritoriesByName(const Territory *a, const Territory *b)
{
    return a->getName() < b->getName();
}

bool compareTerritoriesByArmyCount(const Territory *a, const Territory *b)
{
    return a->getArmies() > b->getArmies();
}

std::map<std::string, std::function<PlayerStrategy *(Player *)>> strategyMap = {
    {"human", [](Player *player)
     { return new HumanPlayerStrategy(player); }},
    {"aggressive", [](Player *player)
     { return new AggressivePlayerStrategy(player); }},
    {"benevolent", [](Player *player)
     { return new BenevolentPlayerStrategy(player); }},
    {"neutral", [](Player *player)
     { return new NeutralPlayerStrategy(player); }},
    {"cheater", [](Player *player)
     { return new CheaterPlayerStrategy(player); }}};

PlayerStrategy *PlayerStrategy::handleStrategyCreation(Player *player, std::string &strategy)
{
    std::string strategy_name;
    for (auto &c : strategy)
    {
        strategy_name += (char)std::tolower(c);
    }

    auto it = strategyMap.find(strategy_name);
    if (it != strategyMap.end())
    {
        PlayerStrategy *newStrategy = (it->second)(player);
        player->setPlayerStrategy(newStrategy);
        newStrategy->setPlayer(player);
        newStrategy->strategyName = strategy_name; // Fix: Assign strategy_name to strategyName member variable
        return newStrategy;
    }
    else
    {
        cout << "Invalid strategy name: " << strategy << endl;
        delete player;
        return nullptr;
    }
}

std::ostream &operator<<(std::ostream &out, const PlayerStrategy &strategy)
{
    if (&strategy == nullptr)
    {
        out << "PlayerStrategy is null";
    }
    else
    {
        strategy.print(out);
    }
    return out;
}

//*******************************************
//  HumanPlayerStrategy Comcrete Class
//*******************************************

HumanPlayerStrategy::HumanPlayerStrategy(Player *player)
{
    this->player = player;
}

void HumanPlayerStrategy::deployArmies(int *armyAvailableCount)
{
    int territoryChoice;
    int armiesToDeployChoice;
    vector<Territory *> territories = toDefend();
    for (int i = 1; i <= territories.size(); i++)
    {
        cout << i << ".\n"
             << *territories[i - 1]
             << "\n"
             << endl;
    }
    cout << "\nWhich territory would you like to deploy to?\n";
    cin >> territoryChoice;
    cout << "\nHow many armies would you like to deploy?\n";
    cin >> armiesToDeployChoice;
    if (*armyAvailableCount < armiesToDeployChoice)
    {
        cout << "You do not have enough armies to deploy that many." << endl;
    }
    else if (territoryChoice < 1 || territoryChoice > territories.size())
    {
        cout << "Invalid territory." << endl;
    }
    else
    {
        territories[territoryChoice - 1]->setArmies(territories[territoryChoice - 1]->getArmies() + armiesToDeployChoice);
        cout << "\n"
             << *territories[territoryChoice - 1] << "\n"
             << endl;
        *armyAvailableCount -= armiesToDeployChoice;
    }

    for (Territory *territory : territories)
    {
        delete territory;
    }
    territories.clear();
}

void HumanPlayerStrategy::advanceArmies()
{
    vector<Territory *> territoriesToDefend = toDefend();
    vector<Territory *> adjacentTerritories;
    int sourceTerritoryChoice = 0, destinationTerritoryChoice = 0, armiesToAdvanceChoice = 0;

    cout << "Please select a territory to advance from: " << endl;

    for (int i = 1; i <= territoriesToDefend.size(); i++)
    {
        if (territoriesToDefend[i - 1]->getArmies() > 1)
        {
            cout << i << ".\n"
                 << *territoriesToDefend[i - 1]
                 << "\n"
                 << endl;
        }
    }

    cin >> sourceTerritoryChoice;
    cout << endl;

    if (sourceTerritoryChoice < 1 || sourceTerritoryChoice > territoriesToDefend.size())
    {
        cout << "Invalid choice." << endl;
        return;
    }

    for (auto &tt : territoriesToDefend[sourceTerritoryChoice - 1]->getAdjacentTerritories())
    {
        adjacentTerritories.push_back(tt.get());
    }

    cout << "Which territory do you want to advance to?" << endl;

    for (int i = 1; i <= adjacentTerritories.size(); i++)
    {
        cout << i << ".\n"
             << *adjacentTerritories[i - 1]
             << "\n"
             << endl;
    }

    cin >> destinationTerritoryChoice;
    cout << endl;

    if (destinationTerritoryChoice < 1 || destinationTerritoryChoice > adjacentTerritories.size())
    {
        cout << "Invalid choice." << endl;
        return;
    }

    cout << "How many armies do you want to advance to " << adjacentTerritories[destinationTerritoryChoice - 1]->getName() << "?" << endl;
    cin >> armiesToAdvanceChoice;
    cout << endl;

    if (armiesToAdvanceChoice < 1 || armiesToAdvanceChoice >= territoriesToDefend[sourceTerritoryChoice - 1]->getArmies())
    {
        cout << "Invalid choice." << endl;
        return;
    }

    int attackArmy = territoriesToDefend[sourceTerritoryChoice - 1]->getArmies();
    int defenceArmy = adjacentTerritories[destinationTerritoryChoice - 1]->getArmies();
    int attackKillCount = 0;
    int defenceKillCount = 0;
    std::shared_ptr<Player> territoryOwnerPtr = adjacentTerritories[destinationTerritoryChoice - 1]->getOwner();
    if (!territoryOwnerPtr)
    {
        cout << "Error: Territory owner is null." << endl;
        return;
    }
    Player *territoryOwner = territoryOwnerPtr.get();

    if (adjacentTerritories[destinationTerritoryChoice - 1]->getOwner().get() == player)
    {
        territoriesToDefend[sourceTerritoryChoice - 1]->setArmies(attackArmy - armiesToAdvanceChoice);
        adjacentTerritories[destinationTerritoryChoice - 1]->setArmies(defenceArmy + armiesToAdvanceChoice);
    }
    else
    {
        cout << "Player was " << territoryOwner->getPlayerStrategy()->getStrategyName() << " and neutral is " << typeid(NeutralPlayerStrategy).name() << endl;
        if (territoryOwner->getPlayerStrategy()->getStrategyName() == "neutral")
        {
            territoryOwner->setPlayerStrategy(new AggressivePlayerStrategy(territoryOwner));
            cout << territoryOwner->getName() << " is now " << *territoryOwner->getPlayerStrategy() << endl;
            return;
        }

        for (int i = 0; i < armiesToAdvanceChoice; i++)
        {
            if (rand() % 100 >= 60)
            {
                defenceKillCount++;
            }
        }

        for (int i = 0; i < defenceArmy; i++)
        {
            if (rand() % 100 >= 70)
            {
                attackKillCount++;
            }
        }

        if (defenceKillCount >= defenceArmy)
        {
            cout << "Defense lost." << endl;
            territoriesToDefend[sourceTerritoryChoice - 1]->setArmies(attackArmy - armiesToAdvanceChoice);
            adjacentTerritories[destinationTerritoryChoice - 1]->setArmies(armiesToAdvanceChoice - attackKillCount);
            player->setTerritories(adjacentTerritories[destinationTerritoryChoice - 1]);
            adjacentTerritories[destinationTerritoryChoice - 1]->setOwner(std::make_shared<Player>(*player));
            player->setConqueredTerritory(true);
            return;
        }
        else if (attackKillCount >= armiesToAdvanceChoice)
        {
            cout << "Attack lost." << endl;
            territoriesToDefend[sourceTerritoryChoice - 1]->setArmies(attackArmy - armiesToAdvanceChoice);
            adjacentTerritories[destinationTerritoryChoice - 1]->setArmies(defenceArmy - defenceKillCount);
            return;
        }
    }

    for (Territory *territory : territoriesToDefend)
    {
        delete territory;
    }

    for (Territory *territory : adjacentTerritories)
    {
        delete territory;
    }

    territoriesToDefend.clear();
    adjacentTerritories.clear();
}

void HumanPlayerStrategy::playCards()
{
    int cardsLeft = player->getHand()->getHandSize();
    int choice;
    cout << *player->getPlayerStrategy();
    cout << "You have " << cardsLeft << " cards in your hand." << endl;
    cout << "Choose card to play:\n"
         << endl;

    int i = 1;
    for (Card *card : player->getHand()->getPlayHand())
    {
        cout << i << ". " << card->getCardType() << endl;
        i++;
    }

    cin >> choice;
    cout << endl;

    if (choice < 1 || choice > cardsLeft)
    {
        cout << "Invalid choice." << endl;
        return;
    }

    player->getHand()->play(choice, *player->getOrdersList());

    cout << "You have " << cardsLeft - 1 << " cards left in your hand." << endl;
    cout << endl;
}

void HumanPlayerStrategy::issueOrder()
{
    int reinforcementPoolLeft = player->getReinforcementPool();
    int cardsLeft = (int)player->getHand()->getHandSize();
    std::string playerName = player->getName();
    int choice;

    std::cout << "Human player " << playerName << " is issuing an order.\n"
              << "You have " << reinforcementPoolLeft << " left for deployment.\n"
              << "You have " << cardsLeft << " cards in your hand.\n"
              << "What's next?\n\n"
              << "1. Deploy\n"
              << "2. Advance\n"
              << "3. Play cards\n"
              << "4. Exit\n\n";

    cin >> choice;

    switch (choice)
    {
    case 1:
        if (reinforcementPoolLeft > 0)
        {
            deployArmies(&reinforcementPoolLeft);
            player->setReinforcementPool(reinforcementPoolLeft);
        }
        else
        {
            cout << "You have no armies left to deploy." << endl;
        }
        break;
    case 2:
        if (reinforcementPoolLeft == 0)
        {
            advanceArmies();
            player->setReinforcementPool(reinforcementPoolLeft);
        }
        else
        {
            cout << "You have more armies left to deploy." << endl;
        }
        break;
    case 3:
        if (cardsLeft > 0)
        {
            playCards();
        }
        else
        {
            cout << "You have more armies left to deploy." << endl;
        }
        break;
    case 4:
        if (reinforcementPoolLeft > 0)
        {
            cout << "You have " << reinforcementPoolLeft << " armies left to deploy." << endl;
            cout << "Deploy all armies before ending your turn." << endl;
        }
        cout << "Exiting..." << endl;
        return;
        break;
    default:
        cout << "Invalid choice." << endl;
        break;
    }
    issueOrder();
}

vector<Territory *> HumanPlayerStrategy::toAttack()
{
    vector<Territory *> possibleToAttack;
    vector<Territory *> ownedTerritories = player->getTerritories();
    for (auto &t : ownedTerritories)
    {
        for (auto &tt : t->getAdjacentTerritories())
        {
            if (find(ownedTerritories.begin(), ownedTerritories.end(), tt.get()) == ownedTerritories.end() &&
                find(possibleToAttack.begin(), possibleToAttack.end(), tt.get()) == possibleToAttack.end())
            {
                possibleToAttack.push_back(tt.get());
            }
        }
    }

    sort(possibleToAttack.begin(), possibleToAttack.end(), compareTerritoriesByName);
    for (Territory *territory : ownedTerritories)
    {
        delete territory;
    }
    ownedTerritories.clear();

    return possibleToAttack;
}

vector<Territory *> HumanPlayerStrategy::toDefend()
{
    if (player == nullptr)
    {
        return vector<Territory *>();
    }
    return player->getTerritories();
}

HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy &strategy)
{
    this->player = new Player(*strategy.player);
}

HumanPlayerStrategy::~HumanPlayerStrategy()
{
    delete player;
}

HumanPlayerStrategy &HumanPlayerStrategy::operator=(const HumanPlayerStrategy &strategy)
{
    if (this != &strategy)
    {
        delete player;
        player = new Player(*strategy.player);
    }
    return *this;
}

//*******************************************
//  AggressivePlayerStrategy Comcrete Class
//*******************************************

AggressivePlayerStrategy::AggressivePlayerStrategy(Player *player)
{
    this->player = player;
}

vector<Territory *> AggressivePlayerStrategy::toAttack()
{
    vector<Territory *> possibleToAttack;
    vector<Territory *> ownedTerritories = player->getTerritories();
    for (auto &t : ownedTerritories)
    {
        for (auto &tt : t->getAdjacentTerritories())
        {
            if (find(ownedTerritories.begin(), ownedTerritories.end(), tt.get()) == ownedTerritories.end() &&
                find(possibleToAttack.begin(), possibleToAttack.end(), tt.get()) == possibleToAttack.end())
            {
                possibleToAttack.push_back(tt.get());
            }
        }
    }

    sort(possibleToAttack.begin(), possibleToAttack.end(), compareTerritoriesByName);
    for (Territory *territory : ownedTerritories)
    {
        delete territory;
    }
    ownedTerritories.clear();
    return possibleToAttack;
}

vector<Territory *> AggressivePlayerStrategy::toDefend()
{
    if (player == nullptr)
    {
        return vector<Territory *>();
    }
    vector<Territory *> listOfTerritories = player->getTerritories();
    if (listOfTerritories.size() == 0)
    {
        return listOfTerritories;
    }
    sort(listOfTerritories.begin(), listOfTerritories.end(), compareTerritoriesByArmyCount);
    return listOfTerritories;
}

void AggressivePlayerStrategy::deployArmies()
{
    int availableArmyCount = player->getReinforcementPool();
    vector<Territory *> territories = toDefend();
    if (territories.size() == 0)
    {
        return;
    }
    territories[0]->setArmies(territories[0]->getArmies() + availableArmyCount);
    player->setReinforcementPool(0);
}

Territory *AggressivePlayerStrategy::advanceArmies(Territory *territory)
{
    if (territory == nullptr)
    {
        cout << "territory is null" << endl;
        return nullptr;
    }
    int availableArmyCount = territory->getArmies();
    if (availableArmyCount == 1)
    {
        return nullptr;
    }

    if (player->getTerritories().size() == mapTerritoriesCount)
    {
        cout << "Player " << player->getName() << " has conquered the world!" << endl;
        return nullptr;
    }
    vector<Territory *> possibleToAttack;
    int armiesToAdvanceCount = availableArmyCount - 1;
    int armiesDefending = 0, defenceDeath = 0, attackDeath = 0;

    for (auto &t : territory->getAdjacentTerritories())
    {
        if (t.get()->getOwner()->getName() != territory->getOwner()->getName() &&
            find(possibleToAttack.begin(), possibleToAttack.end(), t.get()) == possibleToAttack.end())
        {
            possibleToAttack.push_back(t.get());
        }
    }

    vector<Territory *> previousPassedTerritories;
    bool wentInCondition = false;
    while (possibleToAttack.size() == 0)
    {
        previousPassedTerritories.push_back(territory);
        territory->setArmies(0);
        for (auto &t : territory->getAdjacentTerritories())
        {
            if (std::find(previousPassedTerritories.begin(), previousPassedTerritories.end(), t.get()) == previousPassedTerritories.end())
            {
                territory = t.get();
                wentInCondition = true;
                break;
            }
        }
        if(!wentInCondition)
        {
            return nullptr;
        }
        territory->setArmies(territory->getArmies() + armiesToAdvanceCount + 1);
        break;
    }
    
    if (possibleToAttack.size() == 0)
    {
        vector<Territory *> adjacentOwnedTerritories{};
        for (auto &t : territory->getAdjacentTerritories())
        {
            adjacentOwnedTerritories.push_back(t.get());
        }
        sort(adjacentOwnedTerritories.begin(), adjacentOwnedTerritories.end(), compareTerritoriesByArmyCount);
        int randomVariable = rand() % adjacentOwnedTerritories.size();
        adjacentOwnedTerritories[randomVariable]->setArmies(adjacentOwnedTerritories[randomVariable]->getArmies() + armiesToAdvanceCount + 1);
        territory->setArmies(0);
        return adjacentOwnedTerritories[randomVariable];
    }

    std::shared_ptr<Player> territoryOwnerPtr = possibleToAttack[0]->getOwner();
    Player *territoryOwner = territoryOwnerPtr.get();

    if (territoryOwner->getPlayerStrategy()->getStrategyName() == "neutral")
    {
        territoryOwner->setPlayerStrategy(new AggressivePlayerStrategy(territoryOwner));
        cout << territoryOwner->getName() << " is now " << *territoryOwner->getPlayerStrategy() << endl;
    }

    if (possibleToAttack.size() > 0)
    {
        armiesDefending = possibleToAttack[0]->getArmies();
        for (int i = 0; i < armiesToAdvanceCount; i++)
        {
            if (rand() % 100 >= 60)
            {
                defenceDeath++;
            }
        }

        for (int i = 0; i < armiesDefending; i++)
        {
            if (rand() % 100 >= 70)
            {
                attackDeath++;
            }
        }

        if (defenceDeath >= armiesDefending) // Defender loss
        {
            territory->setArmies(1);
            possibleToAttack[0]->setArmies(armiesToAdvanceCount - attackDeath);
            player->setTerritories(possibleToAttack[0]);
            possibleToAttack[0]->setOwner(std::make_shared<Player>(*player));
            player->setConqueredTerritory(true);
            return possibleToAttack[0];
        }
        else if (attackDeath >= armiesToAdvanceCount) // Attack Loss
        {
            territory->setArmies(1);
            possibleToAttack[0]->setArmies(armiesDefending - defenceDeath);
        }
    }
    for (Territory *territory : possibleToAttack)
    {
        delete territory;
    }

    for (Territory *territory : previousPassedTerritories)
    {
        delete territory;
    }
    previousPassedTerritories.clear();
    possibleToAttack.clear();
}

void AggressivePlayerStrategy::issueOrder()
{
    vector<Territory *> territories1 = toDefend();
    Territory *nextTerritory = territories1[0];
    deployArmies();
    do
    {
        cout << *nextTerritory << endl;
        nextTerritory = advanceArmies(nextTerritory);
    } while (nextTerritory != nullptr);
    cout << "\n\n==========================================================================================\n\n";
    for (Territory *territory : territories1)
    {
        delete territory;
    }
    territories1.clear();
}

AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy &strategy)
{
    this->player = new Player(*strategy.player);
}

AggressivePlayerStrategy::~AggressivePlayerStrategy()
{
    delete player;
}

AggressivePlayerStrategy &AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy &strategy)
{
    if (this != &strategy)
    {
        delete player;
        player = new Player(*strategy.player);
    }
    return *this;
}

//*******************************************
//  BenevolentPlayerStrategy Comcrete Class
//*******************************************

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player *player)
{
    this->player = player;
}

// TO IMPLEMENT
vector<Territory *> BenevolentPlayerStrategy::toAttack()
{
    cout << "BenevolentPlayerStrategy::toAttack" << endl;
    return vector<Territory *>();
}

// TO IMPLEMENT
vector<Territory *> BenevolentPlayerStrategy::toDefend()
{
    cout << "BenevolentPlayerStrategy::toDefend" << endl;
    return vector<Territory *>();
}

// TO IMPLEMENT
void BenevolentPlayerStrategy::issueOrder()
{
}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy &strategy)
{
    this->player = new Player(*strategy.player);
}

BenevolentPlayerStrategy::~BenevolentPlayerStrategy()
{
    delete player;
}

BenevolentPlayerStrategy &BenevolentPlayerStrategy::operator=(const BenevolentPlayerStrategy &strategy)
{
    if (this != &strategy)
    {
        delete player;
        player = new Player(*strategy.player);
    }
    return *this;
}

//*******************************************
//  NeutralPlayerStrategy Comcrete Class
//*******************************************

NeutralPlayerStrategy::NeutralPlayerStrategy(Player *player)
{
    this->player = player;
}

vector<Territory *> NeutralPlayerStrategy::toAttack()
{
    return vector<Territory *>();
}

vector<Territory *> NeutralPlayerStrategy::toDefend()
{
    return vector<Territory *>();
}

void NeutralPlayerStrategy::issueOrder()
{
}

NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy &strategy)
{
    this->player = new Player(*strategy.player);
}

NeutralPlayerStrategy::~NeutralPlayerStrategy()
{
    delete player;
}

NeutralPlayerStrategy &NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy &strategy)
{
    if (this != &strategy)
    {
        delete player;
        player = new Player(*strategy.player);
    }
    return *this;
}

//*******************************************
//  CheaterPlayerStrategy Comcrete Class
//*******************************************

CheaterPlayerStrategy::CheaterPlayerStrategy(Player *player)
{
    this->player = player;
}

vector<Territory *> CheaterPlayerStrategy::toAttack()
{
    return vector<Territory *>();
}

vector<Territory *> CheaterPlayerStrategy::toDefend()
{
    if (player == nullptr)
    {
        return vector<Territory *>();
    }
    return player->getTerritories();
}

void CheaterPlayerStrategy::issueOrder()
{
    vector<Territory *> territories = player->getTerritories();
    for (auto &t : territories)
    {
        for (auto &tt : t->getAdjacentTerritories())
        {
            if (find(territories.begin(), territories.end(), tt.get()) == territories.end())
            {
                player->setTerritories(tt.get());
            }
        }
    }

    territories = player->getTerritories();
    for (int i = 1; i <= territories.size(); i++)
    {
        cout << player->getName() << " now owns territories: \n"
             << i << ".\n"
             << *territories[i - 1]
             << "\n"
             << endl;
    }

    for (Territory *territory : territories)
    {
        delete territory;
    }
    territories.clear();
}

CheaterPlayerStrategy::CheaterPlayerStrategy(const CheaterPlayerStrategy &strategy)
{
    this->player = new Player(*strategy.player);
}

CheaterPlayerStrategy::~CheaterPlayerStrategy()
{
    delete player;
}

CheaterPlayerStrategy &CheaterPlayerStrategy::operator=(const CheaterPlayerStrategy &strategy)
{
    if (this != &strategy)
    {
        delete player;
        player = new Player(*strategy.player);
    }
    return *this;
}
