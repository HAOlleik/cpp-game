#include <iostream>
#include <iterator>
#include <map>
#include <string.h>

#include "GameEngine.h"

using namespace std;

map<State, map<Action, State>> mapStateToActions {
    {start, {
        {load_map, map_loaded}
    }},
    {map_loaded, {
        {load_map, map_loaded},
        {validate_map, map_validated}
    }},
    {map_validated, {
        {add_player, players_added}
    }},
    {players_added, {
        {add_player, players_added},
        {assign_countries, assign_reinforcement}
    }},
    {assign_reinforcement, {
        {issue_order, issue_orders}
    }},
    {issue_orders, {
        {issue_order, issue_orders},
        {end_issue_orders, execute_orders}
    }},
    {execute_orders, {
        {exec_order, execute_orders},
        {end_exec_orders, assign_reinforcement},
        {win_game, win}
    }},
    {win, {
        {play, start}
    }}
};

map<string, Action> actionToString {
    {"loadmap", load_map},
    {"validatemap", validate_map},
    {"addplayer", add_player},
    {"assigncountries", assign_countries},
    {"issueorder", issue_order},
    {"endissueorders", end_issue_orders},
    {"execorder", exec_order},
    {"endexecorder", end_exec_orders},
    {"wins", win_game},
    {"play", play},
    {"end", end_game}
};

void testGameEngineStates(){
    State currentState = start;

    while (true) {
        char inputtedAction[50];
        cout << "Please insert next action\n";
        cin >> inputtedAction;
        int inputCharCounter = 0;
        char inputChar;
        while (inputtedAction[inputCharCounter]) {
            inputChar = inputtedAction[inputCharCounter];
            inputtedAction[inputCharCounter] = tolower(inputChar);
            inputCharCounter++;
        }

        if (actionToString[inputtedAction]) {

        } else {
            cout << "Please enter a valid action\n";
        }

        // if (mapStateToActions[currentState].count(action) > 0) {
        //     // Valid action, update the current state
        //     currentState = mapStateToActions[currentState][action];
        //     cout << "Action \"" << inputtedAction << "\" performed. Current state: " << currentState << endl;
        // } else {
        //     cout << "Invalid action \"" << inputtedAction << "\" for current state." << endl;
        // }

    }
};