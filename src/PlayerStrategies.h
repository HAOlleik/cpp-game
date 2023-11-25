#pragma once
#include "Territory.h"
#include <map>
#include <iostream>
#include <vector>
    using std::vector;


// abstract class
class PlayerStrategy{
    public:
        virtual void issueOrder() = 0;
        virtual vector<Territory *> toAttack() = 0;
        virtual vector<Territory *> toDefend() = 0;
        virtual ~PlayerStrategy() = default;
        static PlayerStrategy* handleStrategyCreation(Player* player, std::string& strategy);
        Player* player = nullptr;
};


//concrete strategy class
class HumanPlayerStrategy : public PlayerStrategy{
    public:
        explicit HumanPlayerStrategy(Player* player);
        HumanPlayerStrategy(const HumanPlayerStrategy& strategy);
        ~HumanPlayerStrategy();
        void issueOrder() override;
        vector<Territory *> toAttack() override;
        vector<Territory *> toDefend() override;
        friend std::ostream& operator<<(std::ostream& out, const HumanPlayerStrategy& strategy);
        HumanPlayerStrategy& operator =(const HumanPlayerStrategy& strategy);
};

//concrete strategy class
class AggressivePlayerStrategy : public PlayerStrategy{
     public:
        explicit AggressivePlayerStrategy(Player* player);
        void issueOrder() override;
        vector<Territory *> toAttack() override;
        vector<Territory *> toDefend() override;
};

//concrete strategy class
class BenevolentPlayerStrategy : public PlayerStrategy{
     public:
        explicit BenevolentPlayerStrategy(Player* player);
        void issueOrder() override;
        vector<Territory *> toAttack() override;
        vector<Territory *> toDefend() override;
};

//concrete strategy class
class NeutralPlayerStrategy : public PlayerStrategy{
    public:
        explicit NeutralPlayerStrategy(Player* player);
        void issueOrder() override;
        vector<Territory *> toAttack() override;
        vector<Territory *> toDefend() override;
};

//concrete strategy class
class CheaterPlayerStrategy : public PlayerStrategy{
    public:
        explicit CheaterPlayerStrategy(Player* player);
        void issueOrder() override;
        vector<Territory *> toAttack() override;
        vector<Territory *> toDefend() override;
};

void testPlayerStrategies();

extern std::map<std::string, std::function<PlayerStrategy*(Player*)>> strategyMap;
