#include "PlayerStrategies.h"
    using std::cout;
    using std::endl;

std::map<std::string, std::function<PlayerStrategy*(Player*)>> strategyMap = {
    {"human", [](Player* player) { return new HumanPlayerStrategy(player); }},
    {"aggressive", [](Player* player) { return new AggressivePlayerStrategy(player); }},
    {"benevolent", [](Player* player) { return new BenevolentPlayerStrategy(player); }},
    {"neutral", [](Player* player) { return new NeutralPlayerStrategy(player); }},
    {"cheater", [](Player* player) { return new CheaterPlayerStrategy(player); }},
};

PlayerStrategy* PlayerStrategy::handleStrategyCreation(Player* player, std::string& strategy)
{
    std::string strategy_name;
    for (auto& c : strategy)
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

std::ostream& operator<<(std::ostream& out, const PlayerStrategy& strategy) {
    strategy.print(out);
    return out;
}

//*******************************************
//  HumanPlayerStrategy Comcrete Class
//*******************************************

HumanPlayerStrategy::HumanPlayerStrategy(Player* player){
    this->player = player;
}
//TO IMPLEMENT
vector<Territory *> HumanPlayerStrategy::toAttack(){
    cout<<"HumanPlayerStrategy::toAttack"<<endl;
    return vector<Territory*>();
}

//TO IMPLEMENT
vector<Territory *> HumanPlayerStrategy::toDefend(){
    cout<<"HumanPlayerStrategy::toDefend"<<endl;
    return vector<Territory*>();
}

//TO IMPLEMENT
void HumanPlayerStrategy::issueOrder(){

}

HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy& strategy) {
    this->player = new Player(*strategy.player);
}

HumanPlayerStrategy::~HumanPlayerStrategy() {
    delete player;
}

HumanPlayerStrategy& HumanPlayerStrategy::operator =(const HumanPlayerStrategy& strategy) {
    if (this != &strategy) {
        delete player;
        player = new Player(*strategy.player);
    }
    return *this;
}


//*******************************************
//  AggressivePlayerStrategy Comcrete Class
//*******************************************

AggressivePlayerStrategy::AggressivePlayerStrategy(Player* player){
    this->player = player;
}

//TO IMPLEMENT
vector<Territory *> AggressivePlayerStrategy::toAttack(){
    cout<<"AggressivePlayerStrategy::toAttack"<<endl;
    return vector<Territory*>();
}

//TO IMPLEMENT
vector<Territory *> AggressivePlayerStrategy::toDefend(){
    cout<<"AggressivePlayerStrategy::toDefend"<<endl;
    return vector<Territory*>();
}

//TO IMPLEMENT
void AggressivePlayerStrategy::issueOrder(){

}

AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy& strategy) {
    this->player = new Player(*strategy.player);
}

AggressivePlayerStrategy::~AggressivePlayerStrategy() {
    delete player;
}

AggressivePlayerStrategy& AggressivePlayerStrategy::operator =(const AggressivePlayerStrategy& strategy) {
    if (this != &strategy) {
        delete player;
        player = new Player(*strategy.player);
    }
    return *this;
}

//*******************************************
//  BenevolentPlayerStrategy Comcrete Class
//*******************************************

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* player){
    this->player = player;
}

//TO IMPLEMENT
vector<Territory *> BenevolentPlayerStrategy::toAttack(){
    cout<<"BenevolentPlayerStrategy::toAttack"<<endl;
    return vector<Territory*>();
}

//TO IMPLEMENT
vector<Territory *> BenevolentPlayerStrategy::toDefend(){
    cout<<"BenevolentPlayerStrategy::toDefend"<<endl;
    return vector<Territory*>();
}

//TO IMPLEMENT
void BenevolentPlayerStrategy::issueOrder(){

}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy& strategy) {
    this->player = new Player(*strategy.player);
}

BenevolentPlayerStrategy::~BenevolentPlayerStrategy() {
    delete player;
}

BenevolentPlayerStrategy& BenevolentPlayerStrategy::operator =(const BenevolentPlayerStrategy& strategy) {
    if (this != &strategy) {
        delete player;
        player = new Player(*strategy.player);
    }
    return *this;
}



//*******************************************
//  NeutralPlayerStrategy Comcrete Class
//*******************************************

NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player){
    this->player = player;
}

//TO IMPLEMENT
vector<Territory *> NeutralPlayerStrategy::toAttack(){
    cout<<"NeutralPlayerStrategy::toAttack"<<endl;
    return vector<Territory*>();
}

//TO IMPLEMENT
vector<Territory *> NeutralPlayerStrategy::toDefend(){
    cout<<"NeutralPlayerStrategy::toDefend"<<endl;
    return vector<Territory*>();
}

//TO IMPLEMENT
void NeutralPlayerStrategy::issueOrder(){
    
}

NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy& strategy) {
    this->player = new Player(*strategy.player);
}

NeutralPlayerStrategy::~NeutralPlayerStrategy() {
    delete player;
}

NeutralPlayerStrategy& NeutralPlayerStrategy::operator =(const NeutralPlayerStrategy& strategy) {
    if (this != &strategy) {
        delete player;
        player = new Player(*strategy.player);
    }
    return *this;
}


//*******************************************
//  CheaterPlayerStrategy Comcrete Class
//*******************************************

CheaterPlayerStrategy::CheaterPlayerStrategy(Player* player){
    this->player = player;
}

//TO IMPLEMENT
vector<Territory *> CheaterPlayerStrategy::toAttack(){
    cout<<"CheaterPlayerStrategy::toAttack"<<endl;
    return vector<Territory*>();
}

//TO IMPLEMENT
vector<Territory *> CheaterPlayerStrategy::toDefend(){
    cout<<"CheaterPlayerStrategy::toDefend"<<endl;
    return vector<Territory*>();
}

//TO IMPLEMENT
void CheaterPlayerStrategy::issueOrder(){
    
}

CheaterPlayerStrategy::CheaterPlayerStrategy(const CheaterPlayerStrategy& strategy) {
    this->player = new Player(*strategy.player);
}

CheaterPlayerStrategy::~CheaterPlayerStrategy() {
    delete player;
}

CheaterPlayerStrategy& CheaterPlayerStrategy::operator =(const CheaterPlayerStrategy& strategy) {
    if (this != &strategy) {
        delete player;
        player = new Player(*strategy.player);
    }
    return *this;
}
