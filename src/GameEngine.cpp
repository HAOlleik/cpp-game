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
            // 4) use the gamestart command to
            // a) fairly distribute all the territories to the players
            // b) determine randomly the order of play of the players in the game
            // c) give 50 initial army units to the players, which are placed in their respective reinforcement pool
            // d) let each player draw 2 initial cards from the deck using the deck’s draw() method
            // e) switch the game to the play phase
            randomOrder();
            assignTerritories();

            _deck = std::make_unique<Deck>();
            _deck->fillDeck();
            // for (auto &player : _players)
            // {
            //     player->addReinforcements(50);
            //     // can and wil fail if passed null-ref
            //     player->getHand()->addCard(*_deck->draw());
            //     player->getHand()->addCard(*_deck->draw());
            // }

            *_state = STATE::assign_reinforcement;
            result = "STATE::assign_reinforcement";
            command.saveEffect(result);
            mainGameLoop();
            break;
        }
        case ACTION::load_map:
        {
            // 1) use the loadmap <filename> command to select a map from a list of map files as stored in a directory,
            // which results in the map being loaded in the game.
            MapLoader loader;
            if (!loader.load(request[1]))
            {
                result = "Map was not loaded.";
                std::cout << result << std::endl;
                continue;
            }
            _map = std::make_unique<Map>(*loader.getMap().get());
            *_state = STATE::map_loaded;
            result = "STATE::map_loaded";
            break;
        }

        case ACTION::validate_map:
            // 2) use the validatemap command to validate the map (i.e. it is a connected graph, etc – see assignment 1).
            if (!_map->validate())
            {
                result = "Map is not valid";
                std::cout << result << std::endl;
                continue;
            }

            *_state = STATE::map_validated;
            result = "STATE::map_validated";
            break;

        case ACTION::add_player:
            // 3) use the addplayer <playername> command to enter players in the game (2-6 players)
            *_state = STATE::players_added;
            if (_players.size() == 6)
            {
                result = "Max players count 6 already reach.";
                std::cout << result << std::endl;
                continue;
            }
            _players.push_back(std::make_shared<Player>(new std::string(request[1])));
            result = "STATE::players_added";
            break;

        default:
            break;
        }

        command.saveEffect(result);
    }
}

// This method checks if the player is winner or eliminated
bool GameEngine::conditionToCheckForWinner()
{
    // Check if a single player controls all territories
    int territoriesCount = _map->getTerritories()->size();
    for (const auto &player : _players)
    {
        if (player->getTerritories().size() == territoriesCount)
        {
            // Player controls all territories, declare winner
            std::cout << "Player " << player->getName() << " wins by controlling all territories!" << std::endl;
            return true;
        }
    }

    // Check if any player doesn't control any territory
    for (const auto &player : _players)
    {
        if (player->getTerritories().empty())
        {
            // Player doesn't control any territory, remove from the game
            std::cout << "Player " << player->getName() << " has no territories and is eliminated from the game." << std::endl;
            // Remove the player from the list
            _players.erase(std::remove(_players.begin(), _players.end(), player), _players.end());
            return false; // The game continues after removing the player
        }
    }

    return false; // No winner yet
}

// // play loop
// ACTION GameEngine::mainGameLoop()
// {
//     return ACTION::replay;
// }

ACTION GameEngine::mainGameLoop()
{
    // Continue the game loop until a winner is determined
    while (*_state != STATE::win)
    {
        switch (*_state)
        {
        case STATE::reinforcement_phase:
            reinforcmentPhase(_players);
            break;
        case STATE::issue_orders_phase:
            issueOrdersPhase(_players, _map->getTerritories());
            break;
        case STATE::execute_orders_phase:
            executeOrdersPhase();
            break;
        }

        // Check if a player has won
        if (conditionToCheckForWinner())
        {
            *_state = STATE::win;
            break;
        }

        // Move to the next game state
        // *_state = nextState();  // Implement a function to determine the next game state
    }

    return ACTION::end_game; // Or another appropriate action
}

void GameEngine::randomOrder()
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

void GameEngine::assignTerritories()
{
    auto territoriesCount = _map->getTerritories()->size();
    // get PRGN numbers
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, territoriesCount - 1);

    std::vector<int> distributed;
    uint16_t iter = 0;

    uint16_t prng;
    auto getRandomIndice = [&prng, &dist, &distributed, &rng]()
    {
        while (true)
        {
            prng = dist(rng);
            // if found in already distribiuted indicies
            if (std::find(distributed.begin(), distributed.end(), prng) != distributed.end())
                continue;

            // add indice to distribitued for the next time
            distributed.push_back(prng);
            break;
        }
    };

    while (iter <= (territoriesCount / _players.size()))
    {
        uint16_t userIndex = 0;
        while (userIndex < _players.size())
        {
            getRandomIndice();
            auto it = _map->getTerritories()->begin();
            std::advance(it, prng);
            it->second->setOwner(_players[userIndex]);
            userIndex++;
        }
        // every player should have by one territory by now
        iter++;
    }
}

ostream &operator<<(ostream &os, GameEngine &gameEngine)
{ // insert stream operator
    const char *currentStateString;
    switch (*gameEngine.getState())
    {
    case 5:
        currentStateString = "Assign Reinforcement";
        break;
    case 6:
        currentStateString = "Issue Orders";
        break;
    case 7:
        currentStateString = "Execute Orders";
        break;
    case 8:
        currentStateString = "Win";
        break;
    default:
        break;
    }

    return os << "The current state is: " << currentStateString << "\n\n";
}

// Reinforcement phase
void GameEngine::reinforcmentPhase(vector<shared_ptr<Player>> listPlayer)
{
    bool check = false;
    int temp = 0;
    double count = 0;

    for (int i = 0; i < listPlayer.size(); i++)
    { // check the player's terriotries
        temp = listPlayer[i]->getReinforcementPool();

        for (int j = 0; j < listPlayer[i]->territories.size(); i++)
        { // count the terriorties number
            count++;
        }
        // calculating bonus of continents
        check = (*listPlayer[i]).continentBonusValue();

        if (check == true)
        {
            temp += 2 * (int)round(count / 3);
        }
        else
        {
            temp += (int)round(count / 3);
        }

        temp += 3;
        int *tempPoint = &temp;

        listPlayer[i]->setReinforcementPool(tempPoint);
        check = false;
        temp = 0;
        count = 0;
    }
}

// Issue orders phase
void GameEngine::issueOrdersPhase(std::vector<shared_ptr<Player>> listPlayer, std::shared_ptr<std::map<std::string, std::shared_ptr<Territory>>> map)
{
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
    listPlayer[1]->issueOrder(mapVector);
}

// Execute orders phase
void GameEngine::executeOrdersPhase()
{
}

// Adding players
void GameEngine::addPlayer(const std::string &playerName)
{
    // Ensure the maximum number of players is not exceeded
    if (_players.size() >= 6)
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

void testMainGameLoop()
{
    // Initialize your game engine, map, players, etc.

    // Create a game engine instance
    GameEngine game;

    // Load a map (replace "map_filename.map" with your actual map file)
    MapLoader mapLoader;
    if (mapLoader.load("map_filename.map"))
    {
        game.setMap(std::make_shared<Map>(*mapLoader.getMap()));
        std::cout << "Map loaded successfully." << std::endl;
    }
    else
    {
        std::cerr << "Error: Map could not be loaded." << std::endl;
        return;
    }

    // Add players to the game
    game.addPlayer("Hussein");
    game.addPlayer("Alex");
    // Add more players as needed

    // Start the main game loop
    game.startupPhase(); // Assuming you want to start with the startup phase
}