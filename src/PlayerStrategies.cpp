#include "PlayerStrategies.h"
#include <iostream>
    using std::cout;
    using std::endl;
    
//*******************************************
//  HumanPlayerStrategy Comcrete Class
//*******************************************

HumanPlayerStrategy::HumanPlayerStrategy(){
    cout <<"Called HumanPlayerStrategy"<< endl;
}

//TO IMPLEMENT
vector<Territory *> HumanPlayerStrategy::toAttack(){
    cout<<"HumanPlayerStrategy::toAttack"<<endl;
    //return vector<Territory*>();
}

//TO IMPLEMENT
vector<Territory *> HumanPlayerStrategy::toDefend(){
    cout<<"HumanPlayerStrategy::toDefend"<<endl;
}

//TO IMPLEMENT
void HumanPlayerStrategy::issueOrder(){

}


//*******************************************
//  AggressivePlayerStrategy Comcrete Class
//*******************************************

AggressivePlayerStrategy::AggressivePlayerStrategy(){
    cout <<"Called AggressivePlayerStrategy"<< endl;
}

//TO IMPLEMENT
vector<Territory *> AggressivePlayerStrategy::toAttack(){
    cout<<"AggressivePlayerStrategy::toAttack"<<endl;
}

//TO IMPLEMENT
vector<Territory *> AggressivePlayerStrategy::toDefend(){
    cout<<"AggressivePlayerStrategy::toDefend"<<endl;
}

//TO IMPLEMENT
void AggressivePlayerStrategy::issueOrder(){

}


//*******************************************
//  BenevolentPlayerStrategy Comcrete Class
//*******************************************

BenevolentPlayerStrategy::BenevolentPlayerStrategy(){
    cout <<"Called BenevolentPlayerStrategy"<< endl;
}

//TO IMPLEMENT
vector<Territory *> BenevolentPlayerStrategy::toAttack(){
    cout<<"BenevolentPlayerStrategy::toAttack"<<endl;
}

//TO IMPLEMENT
vector<Territory *> BenevolentPlayerStrategy::toDefend(){
    cout<<"BenevolentPlayerStrategy::toDefend"<<endl;
}

//TO IMPLEMENT
void BenevolentPlayerStrategy::issueOrder(){

}



//*******************************************
//  NeutralPlayerStrategy Comcrete Class
//*******************************************

NeutralPlayerStrategy::NeutralPlayerStrategy(){
    cout <<"Called NeutralPlayerStrategy"<< endl;
}

//TO IMPLEMENT
vector<Territory *> NeutralPlayerStrategy::toAttack(){
    cout<<"NeutralPlayerStrategy::toAttack"<<endl;
}

//TO IMPLEMENT
vector<Territory *> NeutralPlayerStrategy::toDefend(){
    cout<<"NeutralPlayerStrategy::toDefend"<<endl;
}

//TO IMPLEMENT
void NeutralPlayerStrategy::issueOrder(){
    
}


//*******************************************
//  CheaterPlayerStrategy Comcrete Class
//*******************************************

CheaterPlayerStrategy::CheaterPlayerStrategy(){
    cout <<"Called CheaterPlayerStrategy"<< endl;
}

//TO IMPLEMENT
vector<Territory *> CheaterPlayerStrategy::toAttack(){
    cout<<"CheaterPlayerStrategy::toAttack"<<endl;
}

//TO IMPLEMENT
vector<Territory *> CheaterPlayerStrategy::toDefend(){
    cout<<"CheaterPlayerStrategy::toDefend"<<endl;
}

//TO IMPLEMENT
void CheaterPlayerStrategy::issueOrder(){
    
}