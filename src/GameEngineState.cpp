#include "GameEngineState.h"


// transform string to state enum, kind hack
std::map<std::string, STATE> stateMap = {
    {"start", STATE::start},
    {"tournament", STATE::tournament_is_started},
    {"map_loaded", STATE::map_loaded},
    {"map_validated", STATE::map_validated},
    {"players_added", STATE::players_added},
    {"assign_reinforcement", STATE::assign_reinforcement},
    {"issue_orders", STATE::issue_orders},
    {"execute_orders", STATE::execute_orders},
    {"win", STATE::win},
    {"game_ended", STATE::game_ended},
};

// transform string to action enum, kind hack
std::map<std::string, ACTION> actionMap = {
    {"load_map", ACTION::load_map},
    {"tournament", ACTION::tournament},
    {"validate_map", ACTION::validate_map},
    {"add_player", ACTION::add_player},
    {"gamestart", ACTION::gamestart},
    {"assign_countries", ACTION::assign_countries},
    {"issue_order", ACTION::issue_order},
    {"end_issue_orders", ACTION::end_issue_orders},
    {"exec_order", ACTION::exec_order},
    {"end_exec_orders", ACTION::end_exec_orders},
    {"win_game", ACTION::win_game},
    {"end_game", ACTION::end_game},
    {"replay", ACTION::replay},
};

// map of possible actions from a state, and the leading state of that action
std::map<STATE, std::map<ACTION, STATE>> mapStateToActions{
    {STATE::start, {{ACTION::tournament, STATE::tournament_is_started}}},
    {STATE::start, {{ACTION::load_map, STATE::map_loaded}}},
    {STATE::tournament_is_started, {{ACTION::load_map, STATE::map_loaded}}},
    {STATE::map_loaded, {{ACTION::load_map, STATE::map_loaded}, {ACTION::validate_map, STATE::map_validated}}},
    {STATE::map_validated, {{ACTION::add_player, STATE::players_added}}},
    {STATE::players_added, {{ACTION::add_player, STATE::players_added}, {ACTION::gamestart, STATE::assign_reinforcement}}},
    {STATE::assign_reinforcement, {{ACTION::issue_order, STATE::issue_orders}}},
    {STATE::issue_orders, {{ACTION::issue_order, STATE::issue_orders}, {ACTION::end_issue_orders, STATE::execute_orders}}},
    {STATE::execute_orders, {{ACTION::exec_order, STATE::execute_orders}, {ACTION::end_exec_orders, STATE::assign_reinforcement}, {ACTION::win_game, STATE::win}}},
    {STATE::win, {{ACTION::end_game, STATE::game_ended}, {ACTION::replay, STATE::start}}}};