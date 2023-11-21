#include "GameEngine.h"
#include "Territory.h"

// default constructor
GameEngine::GameEngine()
{
    _state = std::make_shared<STATE>(STATE::start);
    _cli = std::make_unique<CommandProcessor>();
}

// parametrized contructor
GameEngine::GameEngine(CommandProcessor cli)
{
    _state = std::make_shared<STATE>(STATE::start);
    _cli = std::make_unique<CommandProcessor>(cli);
}

// copy constructor
GameEngine::GameEngine(const GameEngine &g)
{
    _state = std::make_shared<STATE>(*g.getState());
}

// destructor
GameEngine::~GameEngine()
{
    _state = nullptr;
    _players.clear();
    _map = nullptr;
    _cli = nullptr;
    std::cout << "Game engine destroyed\n";
}

// assignment operator overload
GameEngine &GameEngine::operator=(const GameEngine &g)
{
    _state = std::make_shared<STATE>(*g.getState());
    _map = std::make_unique<Map>(*g._map.get());
    // finish this because need deep copy of map and etc
    return *this;
}

// startup loop
void GameEngine::startupPhase()
{
    while (*_state != STATE::win)
    {
        std::string result;

        // getCommand(currentStaet:state) -> process
        Command command = _cli->getCommand(*(_state.get()));

        // need to discuss what to do with this
        // effect represent error from command at the initial stage
        if ((result = command.getEffect()) != "")
        {
            std::cout << result << std::endl;
            continue;
        }

        // split command argument
        // 0 command 1 argument
        std::stringstream ss(command.getCommand());
        std::vector<std::string> request;

        std::string buffer;
        while (std::getline(ss, buffer, ' '))
        {
            request.push_back(buffer);
        }

        // if effect is not empty then it is an error
        switch (actionMap[request[0]])
        {
        case ACTION::gamestart:
        {
            assignPlayersRandomOrder();
            assignTerritoriesPlayers();

            // initial size of the deck is 10
            _deck = std::make_unique<Deck>(10);
            _deck->fillDeck();
            for (auto &player : _players)
            {
                player->addReinforcements(50);
                // can and wil fail if passed null-ref
                player->getHand()->addCard(*_deck->draw());
                player->getHand()->addCard(*_deck->draw());
            }

            setState(STATE::assign_reinforcement);
            result = "STATE::assign_reinforcement";
            command.saveEffect(result);
            mainGameLoop();
            break;
        }
        case ACTION::load_map:
        {
            MapLoader loader;
            if (!loader.load(request[1]))
            {
                result = "Map was not loaded.";
                std::cout << result << std::endl;
                continue;
            }

            _map = std::make_unique<Map>(*loader.getMap().get());
            setState(STATE::map_loaded);
            result = "STATE::map_loaded";
            cout << result;
            break;
        }

        case ACTION::validate_map:
            if (!_map->validate())
            {
                result = "Map is not valid";
                std::cout << result << std::endl;
                continue;
            }

            setState(STATE::map_validated);
            result = "STATE::map_validated";
            break;

        case ACTION::add_player:
            addPlayer(request[1]);
            setState(STATE::players_added);
            result = "STATE::players_added";
            break;

        default:
            continue;
        }

        command.saveEffect(result);
    }
}

// This method checks if the player is winner or eliminated
bool GameEngine::conditionToCheckForWinner()
{
    // Check if a single player controls all territories
    uint64_t territoriesCount = _map->getTerritories()->size();
    for (const auto &player : _players)
    {
        if (player->getTerritories().size() == territoriesCount)
        {
            // Player controls all territories, declare winner
            return true;
        }
    }

    return false; // No winner yet
}

ACTION GameEngine::mainGameLoop()
{
    // This loop shall continue until only one of the players owns all the territories in the map, at which point a winner is
    // announced and the game ends. The main game loop also checks for any player that does not control at least one
    // territory;
    // if so, the player is removed from the game.

    // Continue the game loop until a winner is determined
    // when we come first state

    setState(STATE::assign_reinforcement);
    while (*_state != STATE::win)
    {
        switch (*_state)
        {
        case STATE::assign_reinforcement:
            reinforcmentPhase();
            break;
        case STATE::issue_orders:
            issueOrdersPhase();
            break;
        case STATE::execute_orders:
            executeOrdersPhase();
            break;
            // to catch all other cases so we have no warning
        default:
            continue;
        }

        // Check if a player has won
        if (conditionToCheckForWinner())
        {
            std::cout << "Player " << _players[1]->getName() << " wins by controlling all territories!" << std::endl;
            setState(STATE::win);
            break;
        }

        checkLoosers();

        // Move to the next game state
        // *_state = nextState();  // Implement a function to determine the next game state
    }
    return ACTION::end_game; // Or another appropriate action
}

void GameEngine::checkLoosers()
{
    // Check if any player doesn't control any territory
    for (const auto &player : _players)
    {
        if (player->getTerritories().empty())
        {
            // Player doesn't control any territory, remove from the game
            std::cout << "Player " << player->getName() << " has no territories and is eliminated from the game." << std::endl;
            // Remove the player from the list
            _players.erase(std::remove(_players.begin(), _players.end(), player), _players.end());
        }
    }

    // for (auto &player : _players)
    // {
    //     // if a player has 0 terr, remove looser
    //     if (player->getTerritories().size() == 0)
    //         _players.erase(std::remove(_players.begin(), _players.end(), player), _players.end());
    // }
}

void GameEngine::assignPlayersRandomOrder()
{
    // get PRGN numbers
    std::random_device dev;
    std::mt19937 rng(dev());
    std::vector<std::shared_ptr<Player>> tempPlayers = _players;
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, tempPlayers.size() - 1);
    std::vector<uint16_t> order;
    uint16_t prng = dist6(rng);
    // while number is not already in the array
    // and size of order is <= than players
    while (
        std::find(order.begin(), order.end(), prng) == order.end() && order.size() < tempPlayers.size())
    {
        order.push_back(prng);
        prng = dist6(rng);
    }

    std::shared_ptr<Player> temp;
    for (size_t i = 0; i < tempPlayers.size(); i++)
    {
        std::vector<uint16_t>::iterator position = std::find(order.begin(), order.end(), i);
        auto newPosition = position - order.begin();
        temp = tempPlayers[i];
        tempPlayers[i] = tempPlayers[newPosition];
        tempPlayers[newPosition] = temp;
    }

    _players = tempPlayers; // overwrite with random order
}

void GameEngine::assignTerritoriesPlayers()
{
    auto terr = _map->getTerritories();

    uint64_t iter = 0;
    for (auto &it : *terr)
    {
        it.second->setOwner(_players[iter % _players.size()]);
        // add terr pointer to player
        _players[iter % _players.size()]->setTerritories(it.second.get());
        iter++;
    }
}

ostream &operator<<(ostream &os, GameEngine &gameEngine)
{ // insert stream operator
    // const char *currentStateString;
    // switch (*gameEngine.getState())
    // {
    // case 5:
    //     currentStateString = "Assign Reinforcement";
    //     break;
    // case 6:
    //     currentStateString = "Issue Orders";
    //     break;
    // case 7:
    //     currentStateString = "Execute Orders";
    //     break;
    // case 8:
    //     currentStateString = "Win";
    //     break;
    // default:
    //     break;
    // }

    return os << "The current state is: "
              << "currentStateString"
              << "\n\n";
}

// Reinforcement phase
void GameEngine::reinforcmentPhase()
{
    // Reinforcement Phase—Players are given a number of army units that depends on the number of
    // territories they own, (# of territories owned divided by 3, rounded down). If the player owns all the
    // territories of an entire continent, the player is given a number of army units corresponding to the
    // continent’s control bonus value. In any case, the minimal number of reinforcement army units per turn for
    // any player is 3. These army units are placed in the player’s reinforcement pool. This must be
    // implemented in a function/method named reinforcementPhase() in the game engine.
    for (auto &player : _players)
    {

        int currentRPool = 0;
        uint32_t count = 0;

        // check the player's terriotries
        currentRPool = player->getReinforcementPool();

        // count the terriorties number
        count = player->territories.size();

        // adding bonus of continents
        currentRPool += player->continentBonusValue();

        // # terr / 3
        currentRPool += floor(count / 3);

        // minimum reinforcement
        currentRPool += 3;

        player->setReinforcementPool(currentRPool);
    }

    // move to the next phase
    setState(STATE::issue_orders);
}

// Issue orders phase, should be round-robin
void GameEngine::issueOrdersPhase()
{
    // Issuing Orders Phase—Players issue orders and place them in their order list through a call to the
    // Player::issueOrder() method. This method is called in round-robin fashion across all players by the
    // game engine. This phase ends when all players have signified that they don’t have any more orders to
    // issue for this turn. This must be implemented in a function/method named issueOrdersPhase() in the
    // game engine.
    std::shared_ptr<std::map<std::string, std::shared_ptr<Territory>>> map = _map->getTerritories();

    if (_map == nullptr)
    {
        std::cerr << "Error: Map is nullptr in issueOrdersPhase." << std::endl;
        return;
    }

    // Ensure Map is valid
    if (!map)
    {
        std::cerr << "Error: Null Map in issueOrdersPhase." << std::endl;
        return;
    }

    // Convert territories in Map to std::vector<Territory *>
    std::vector<Territory *> mapVector;
    for (const auto &entry : *map)
    {
        mapVector.push_back(entry.second.get());
    }

    // Call issueOrder with the converted vector
    _players[1]->issueOrder();

    // move to the next phase
    setState(STATE::execute_orders);
}

// Execute orders phase
void GameEngine::executeOrdersPhase()
{
    // Orders Execution Phase—Once all the players have signified in the same turn that they are not issuing
    // one more order, the game engine proceeds to execute the top order on the list of orders of each player in a round-robin fashion(i.e.the “Order Execution Phase”—see below).Once all the players’ orders have been executed, the main game loop goes back to the reinforcement phase.This must be implemented in a function / method named executeOrdersPhase() in the game engine.

    // Iterate through each player and execute their top order
    bool haveOrdersToExecute = true;
    while (haveOrdersToExecute)
    {
        std::vector<bool> playerLeftOrders;
        for (auto &player : _players)
        {
            // Get the player's orders
            list<Order *> orders = player->getOrders();

            // Execute the top order if there are any orders
            if (orders.empty())
                continue;

            playerLeftOrders.push_back(false);

            if (!orders.empty())
            {
                orders.front()->execute();
                orders.pop_front();
            }
            else
            {
                continue;
            }

            std::cout << "Player " << player->getName() << " executed an order." << std::endl;
            player->orders = orders;
        }

        std::cout << "readched 7 "
                  << "size of nothing " << playerLeftOrders.size() << " size of player " << _players.size() << std::endl;
        // Check if any player still has orders to execute
        if (playerLeftOrders.empty()) {
            haveOrdersToExecute = false;
        }
    }

    std::cout << "Exit from execute order" << std::endl;

    // No remaining orders for any player, move back to the reinforcement phase
    setState(STATE::assign_reinforcement);
}

// Adding players
void GameEngine::addPlayer(const std::string &playerName)
{
    // Ensure the maximum number of players is not exceeded
    if (_players.size() >= MAX_PLAYERS)
    {
        std::cerr << "Error: Maximum number of players reached (6 players)." << std::endl;
        return;
    }

    // Check if the player with the same name already exists
    auto existingPlayer = std::find_if(_players.begin(), _players.end(),
                                       [&playerName](const auto &player)
                                       {
                                           return player->getName() == playerName;
                                       });

    if (existingPlayer != _players.end())
    {
        std::cerr << "Error: Player with the same name already exists." << std::endl;
        return;
    }

    // Create a new player and add it to the players vector
    auto newPlayer = std::make_shared<Player>(new std::string(playerName));
    _players.push_back(newPlayer);

    std::cout << "Player " << playerName << " added to the game." << std::endl;
}

// set map
void GameEngine::setMap(std::shared_ptr<Map> map)
{
    _map = std::make_unique<Map>(*map);
}

#include "GameEngineState.h"

std::string GameEngine::getStateAsString(STATE state)
{
    switch (state)
    {
    case STATE::start:
        return "Start";
    case STATE::map_loaded:
        return "Map Loaded";
    case STATE::map_validated:
        return "Map Validated";
    case STATE::players_added:
        return "Players added";
    case STATE::assign_reinforcement:
        return "Assign reinforcement";
    case STATE::issue_orders:
        return "Issue orders";
    case STATE::execute_orders:
        return "Execute orders";
    case STATE::win:
        return "Win";
    case STATE::game_ended:
        return "Game ended";
    // Add cases for other states
    default:
        return "Unknown State";
    }
}

string GameEngine::stringToLog()
{
    string returnString = "The new game state is: ";

    if (_state)
    {
        string gameStateDetails = getStateAsString(*_state); // Assuming _state is a pointer to a STATE enum

        return returnString + gameStateDetails;
    }
    else
    {
        return returnString + "No game state available.";
    }
}

void testMainGameLoop()
{
    // Initialize your game engine, map, players, etc.

    // Create a game engine instance
    GameEngine game;

    // // Load a map (replace "map_filename.map" with your actual map file)
    // MapLoader mapLoader;
    // if (mapLoader.load("maps/Alberta/Alberta.map"))
    // {
    //     game.setMap(std::make_shared<Map>(*mapLoader.getMap()));
    //     std::cout << "Map loaded successfully." << std::endl;
    // }
    // else
    // {
    //     std::cerr << "Error: Map could not be loaded." << std::endl;
    //     return;
    // }

    // // Add players to the game
    // game.addPlayer("Hussein");
    // game.addPlayer("Alex");
    // // Add more players as needed

    // // Start the main game loop
    game.startupPhase(); // Assuming you want to start with the startup phase
}