#include "PlayerStrategies.h"

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
     { return new CheaterPlayerStrategy(player); }},
};

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
        return (it->second)(player);
    }
    else
    {
        cout << "Invalid strategy name: " << strategy << endl;
        return nullptr;
    }
}

std::ostream &operator<<(std::ostream &out, const PlayerStrategy &strategy)
{
    strategy.print(out);
    return out;
}

//*******************************************
//  HumanPlayerStrategy Comcrete Class
//*******************************************

HumanPlayerStrategy::HumanPlayerStrategy(Player *player)
{
    this->player = player;
}

void HumanPlayerStrategy::deployArmies(int *armyCount)
{
    int territoryChoice;
    int armiesToDeployChoice;
    vector<Territory *> territories = player->getTerritories();
    for (int i = 0; i < territories.size(); i++)
    {
        cout << i << ".\n"
             << *territories[i]
             << "\n"
             << endl;
    }
    cout << "\nWhich territory would you like to deploy to?\n";
    cin >> territoryChoice;
    cout << "\nHow many armies would you like to deploy?\n";
    cin >> armiesToDeployChoice;
    if (*armyCount < armiesToDeployChoice)
    {
        cout << "You do not have enough armies to deploy that many." << endl;
    }
    else
    {
        territories[territoryChoice]->setArmies(territories[territoryChoice]->getArmies() + armiesToDeployChoice);
        cout << "\n"
             << *territories[territoryChoice] << "\n"
             << endl;
        *armyCount -= armiesToDeployChoice;
    }
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
              << "4. Exit\n"
              << "5. Finished issuing orders for the entire turn\n\n";

    cin >> choice;

    switch (choice)
    {
    case 1:
        if (reinforcementPoolLeft > 0)
        {
            deployArmies(&reinforcementPoolLeft);
            player->setReinforcementPool(reinforcementPoolLeft);
            issueOrder();
        }
        else
        {
            cout << "You have no armies left to deploy." << endl;
            issueOrder();
        }
        break;
    case 2:
        // if (!advance())
        // {
        //     issueOrder();
        // }
        break;
    case 3:
        // if (cardsLeft > 0)
        // {
        //     if (!playCard())
        //     {
        //         issueOrder();
        //     }
        // }
        // else
        // {
        //     cout << "You have no cards to play." << endl;
        //     issueOrder();
        // }
        break;
    case 4:
        cout << "Exiting..." << endl;
        break;
    case 5:
        if (reinforcementPoolLeft > 0)
        {
            cout << "You have " << reinforcementPoolLeft << " armies left to deploy." << endl;
            cout << "You must deploy all armies before you can end your turn." << endl;
            issueOrder();
        }
        break;
    default:
        cout << "Invalid choice." << endl;
        issueOrder();
        break;
    }
}

// TO IMPLEMENT
vector<Territory *> HumanPlayerStrategy::toAttack()
{
    cout << "HumanPlayerStrategy::toAttack" << endl;
    return vector<Territory *>();
}

// TO IMPLEMENT
vector<Territory *> HumanPlayerStrategy::toDefend()
{
    cout << "HumanPlayerStrategy::toDefend" << endl;
    return vector<Territory *>();
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

// TO IMPLEMENT
vector<Territory *> AggressivePlayerStrategy::toAttack()
{
    cout << "AggressivePlayerStrategy::toAttack" << endl;
    return vector<Territory *>();
}

// TO IMPLEMENT
vector<Territory *> AggressivePlayerStrategy::toDefend()
{
    cout << "AggressivePlayerStrategy::toDefend" << endl;
    return vector<Territory *>();
}

// TO IMPLEMENT
void AggressivePlayerStrategy::issueOrder()
{
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

// TO IMPLEMENT
vector<Territory *> NeutralPlayerStrategy::toAttack()
{
    cout << "NeutralPlayerStrategy::toAttack" << endl;
    return vector<Territory *>();
}

// TO IMPLEMENT
vector<Territory *> NeutralPlayerStrategy::toDefend()
{
    cout << "NeutralPlayerStrategy::toDefend" << endl;
    return vector<Territory *>();
}

// TO IMPLEMENT
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

// TO IMPLEMENT
vector<Territory *> CheaterPlayerStrategy::toAttack()
{
    cout << "CheaterPlayerStrategy::toAttack" << endl;
    return vector<Territory *>();
}

// TO IMPLEMENT
vector<Territory *> CheaterPlayerStrategy::toDefend()
{
    cout << "CheaterPlayerStrategy::toDefend" << endl;
    return vector<Territory *>();
}

// TO IMPLEMENT
void CheaterPlayerStrategy::issueOrder()
{
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
