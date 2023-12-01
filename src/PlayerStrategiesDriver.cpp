#include <string>
#include <vector>
#include <random>

#include "GameEngine.h"
#include "Drivers.h"
#include "PlayerStrategies.h"
#include "GlobalVariables.h"

int mapTerritoriesCount = 0;

void testPlayerStrategies() {
    GameEngine game;
    MapLoader loader;
    loader.load("maps/Alberta/Alberta.map"); //path for Linux, for Windows change to '../maps/Alberta/Alberta.map'
    game.setMap(loader.getMap());
    auto territories = loader.getMap()->getTerritories();
    mapTerritoriesCount = territories->size();

    // Create players
    std::string name1 = "pl1";
    std::string name2 = "pl2";
    std::string neutral = "neutral";

    std::shared_ptr<Player> player1 = std::make_shared<Player>(&name1);
    std::shared_ptr<Player> player2 = std::make_shared<Player>(&name2);

    // Fill player1's hand with cards
    player1->getHand()->getDeck()->fillDeck();
    Deck testDeck = *player1->getHand()->getDeck();
    player1->getHand()->addCard(*testDeck.draw());
    player1->getHand()->addCard(*testDeck.draw());
    player1->getHand()->addCard(*testDeck.draw());

    // Fill player2's hand with cards
    player2->getHand()->addCard(*testDeck.draw());
    player2->getHand()->addCard(*testDeck.draw());
    player2->getHand()->addCard(*testDeck.draw());

    // Assign territories to players
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    for (auto &territoryPair : *territories) {
        Territory *territory = territoryPair.second.get();
        territory->setArmies(rand() % 10 + 1);

        if (dis(gen) == 0) {
            player1->setTerritories(territory);
            territory->setOwner(player1);
        } else {
            player2->setTerritories(territory);
            territory->setOwner(player2);
        }
    }

    // Set initial reinforcement pools
    player1->setReinforcementPool(50);
    player2->setReinforcementPool(50);

    std::string strategyName = "";
    while (true) {
        std::cout << "Next\nPlease enter player1's strategy name (or 'exit' to quit):\n";
        std::cin >> strategyName;

        if (strategyName == "exit") {
            break;
        }

        // Create player strategies
        PlayerStrategy *strategy1 = PlayerStrategy::handleStrategyCreation(player1.get(), strategyName);
        PlayerStrategy *strategy2 = PlayerStrategy::handleStrategyCreation(player2.get(), neutral);

        // Display the chosen strategy
        std::cout << *strategy1 << std::endl;

        // Execute player1's strategy
        strategy1->issueOrder();

        // Check for conquered territory
        if (player1->getConqueredTerritory()) {
            player1->getHand()->addCard(*testDeck.draw());
            player1->setConqueredTerritory(false);
        }
    }
}