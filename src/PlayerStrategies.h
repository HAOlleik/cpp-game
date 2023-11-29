#pragma once
#include "Territory.h"
#include "Player.h"
#include <map>
#include <iostream>
#include <vector>
#include <functional>
using namespace std;

// abstract class
class PlayerStrategy{
    public:
        virtual void issueOrder() = 0;
        virtual vector<Territory *> toAttack() = 0;
        virtual vector<Territory *> toDefend() = 0;
        virtual ~PlayerStrategy() { delete player; };
        virtual void print(std::ostream& out) const = 0;
        static PlayerStrategy* handleStrategyCreation(Player* player, std::string& strategy);
        void setPlayer(Player* player) { this->player = player; };
        Player* player;
        string strategyName;
        string getStrategyName() { return strategyName; };
        friend std::ostream& operator<<(std::ostream& out, const PlayerStrategy& strategy);
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
        void print(std::ostream& out) const override {
            out << "HumanPlayerStrategy";
        }
        HumanPlayerStrategy& operator =(const HumanPlayerStrategy& strategy);
        void deployArmies(int* armyAvailableCount);
        void advanceArmies();
        void playCards();
};

//concrete strategy class
class AggressivePlayerStrategy : public PlayerStrategy{
     public:
        explicit AggressivePlayerStrategy(Player* player);
        AggressivePlayerStrategy(const AggressivePlayerStrategy& strategy);
        ~AggressivePlayerStrategy();
        void issueOrder() override;
        vector<Territory *> toAttack() override;
        vector<Territory *> toDefend() override;
        void print(std::ostream& out) const override {
            out << "AggressivePlayerStrategy";
        }
        AggressivePlayerStrategy& operator =(const AggressivePlayerStrategy& strategy);
};

//concrete strategy class
class BenevolentPlayerStrategy : public PlayerStrategy{
     public:
        explicit BenevolentPlayerStrategy(Player* player);
        BenevolentPlayerStrategy(const BenevolentPlayerStrategy& strategy);
        ~BenevolentPlayerStrategy();
        void issueOrder() override;
        vector<Territory *> toAttack() override;
        vector<Territory *> toDefend() override;
        void print(std::ostream& out) const override {
            out << "BenevolentPlayerStrategy";
        }
        BenevolentPlayerStrategy& operator =(const BenevolentPlayerStrategy& strategy);
};

//concrete strategy class
class NeutralPlayerStrategy : public PlayerStrategy{
    public:
        explicit NeutralPlayerStrategy(Player* player);
        NeutralPlayerStrategy(const NeutralPlayerStrategy& strategy);
        ~NeutralPlayerStrategy();
        void issueOrder() override;
        vector<Territory *> toAttack() override;
        vector<Territory *> toDefend() override;
        void print(std::ostream& out) const override {
            out << "NeutralPlayerStrategy";
        }
        NeutralPlayerStrategy& operator =(const NeutralPlayerStrategy& strategy);
};

//concrete strategy class
class CheaterPlayerStrategy : public PlayerStrategy{
    public:
        explicit CheaterPlayerStrategy(Player* player);
        CheaterPlayerStrategy(const CheaterPlayerStrategy& strategy);
        ~CheaterPlayerStrategy();
        void issueOrder() override;
        vector<Territory *> toAttack() override;
        vector<Territory *> toDefend() override;
        void print(std::ostream& out) const override {
            out << "CheaterPlayerStrategy";
        }
        CheaterPlayerStrategy& operator =(const CheaterPlayerStrategy& strategy);
};

void testPlayerStrategies();

extern std::map<std::string, std::function<PlayerStrategy*(Player*)>> strategyMap;

std::ostream& operator<<(std::ostream& out, const PlayerStrategy& strategy);
