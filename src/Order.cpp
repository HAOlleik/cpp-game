#include "Order.h"

Order::Order() {}

DeployOrder::DeployOrder() {}
DeployOrder::DeployOrder() : Order(new std::string("Deploy"))
{
    // Constructor sets the orderName to "Deploy"
}
bool DeployOrder::validate(){
    return true;
}


AdvanceOrder::AdvanceOrder(){}
AdvanceOrder::AdvanceOrder() : Order(new std::string("Advance"))
{
    // Constructor sets the orderName to "Advance"
}
bool AdvanceOrder::validate()
{
    return true;
}


BombOrder::BombOrder(){}
BombOrder::BombOrder() : Order(new std::string("Bomb"))
{
    // Constructor sets the orderName to "Bomb"
}
bool BombOrder::validate()
{
    return true;
}


BlockadeOrder::BlockadeOrder(){}
BlockadeOrder::BlockadeOrder() : Order(new std::string("Blockade"))
{
    // Constructor sets the orderName to "Blockade"
}
bool BlockadeOrder::validate()
{
    return true;
}


AirliftOrder::AirliftOrder(){}
AirliftOrder::AirliftOrder() : Order(new std::string("Airlift"))
{
    // Constructor sets the orderName to "Airlift"
}
bool AirliftOrder::validate()
{
    return true;
}


NegotiateOrder::NegotiateOrder(){}
NegotiateOrder::NegotiateOrder() : Order(new std::string("Negotiate"))
{
    // Constructor sets the orderName to "Negotiate"
}
bool NegotiateOrder::validate()
{
    return true;
}