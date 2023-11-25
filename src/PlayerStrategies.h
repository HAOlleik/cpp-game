#pragma once
#include "Territory.h"
#include <vector>
    using std::vector;
class Territory;

// abstract class
class PlayerStrategy{
    public:
        virtual void issueOrder() = 0;
        virtual vector<Territory *> toAttack() = 0;
        virtual vector<Territory *> toDefend() = 0;

        virtual ~PlayerStrategy() = default;
};

//concrete strategy class
class HumanPlayerStrategy : public PlayerStrategy{
    public:
        HumanPlayerStrategy();
        void issueOrder();
        vector<Territory *> toAttack();
        vector<Territory *> toDefend();
};

//concrete strategy class
class AggressivePlayerStrategy : public PlayerStrategy{
     public:
        AggressivePlayerStrategy();
        void issueOrder();
        vector<Territory *> toAttack();
        vector<Territory *> toDefend();
};

//concrete strategy class
class BenevolentPlayerStrategy : public PlayerStrategy{
     public:
        BenevolentPlayerStrategy();
        void issueOrder();
        vector<Territory *> toAttack();
        vector<Territory *> toDefend();
};

//concrete strategy class
class NeutralPlayerStrategy : public PlayerStrategy{
    public:
        NeutralPlayerStrategy();
        void issueOrder();
        vector<Territory *> toAttack();
        vector<Territory *> toDefend();
};

//concrete strategy class
class CheaterPlayerStrategy : public PlayerStrategy{
    public:
        CheaterPlayerStrategy();
        void issueOrder();
        vector<Territory *> toAttack();
        vector<Territory *> toDefend();
};

void testPlayerStrategies();