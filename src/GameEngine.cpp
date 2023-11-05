#include "GameEngine.h"

// default constructor
GameEngine::GameEngine()
{
    _state = std::make_shared<STATE>(STATE::start);
    cli = std::make_unique<CommandProcessor>();
}

// parametrized contructor
GameEngine::GameEngine(CommandProcessor cli)
{
    _state = std::make_shared<STATE>(STATE::start);
    cli = cli;
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
    cli = nullptr;
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
        Command command = cli->getCommand(*(_state.get()));

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

            // get PRGN numbers
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 6);

            std::vector<std::shared_ptr<Player>> tempPlayers = _players;

            *_state = STATE::start;
            result = "STATE::start";
            command.saveEffect(result);
            playPhase();
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

// play loop
ACTION GameEngine::playPhase()
{
    return ACTION::replay;
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
