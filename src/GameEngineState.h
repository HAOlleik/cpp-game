#pragma once

#include <map>
#include <string>

// available states
enum STATE
{
    start = 1,
    tournament_is_started,
    map_loaded,
    map_validated,
    players_added,
    assign_reinforcement,
    issue_orders,
    execute_orders,
    win,
    game_ended,
    tournament_is_finished,

    // this should be remove, cause names are incorrect per part A, look carefully
    reinforcement_phase, // Part 3 2023-11-11
    issue_orders_phase,  // Part 3 2023-11-11
    execute_orders_phase // Part 3 2023-11-11
};

// transform string to state enum, kind hack
extern std::map<std::string, STATE> stateMap;

// available actions
enum ACTION
{
    tournament = 1,
    load_map,
    validate_map,
    add_player,
    gamestart,
    assign_countries,
    issue_order,
    end_issue_orders,
    exec_order,
    end_exec_orders,
    win_game,
    end_game,
    replay
};

// transform string to action enum, kind hack
extern std::map<std::string, ACTION> actionMap;

// map of possible actions from a state, and the leading state of that action
extern std::map<STATE, std::map<ACTION, STATE>> mapStateToActions;