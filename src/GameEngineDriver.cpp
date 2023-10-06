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
    {"endexecorders", end_exec_orders},
    {"win", win_game},
    {"play", play},
    {"end", end_game}
};

int inputCharCounter;

void testGameEngineStates(){
    State currentState = win;
    State nextState;

    while (true) {
        std::cout << "The current state is: ";
        switch (currentState)
        {
        case 0:
            std::cout << "Start";
            break;

        case 1:
            std::cout << "Map Loaded";
            break;

        case 2:
            std::cout << "Map Validated";
            break;

        case 3:
            std::cout << "Players Added";
            break;

        case 4:
            std::cout << "Assign Reinforcement";
            break;

        case 5:
            std::cout << "Issue Orders";
            break;

        case 6:
            std::cout << "Execute Orders";
            break;

        case 7:
            std::cout << "Win";
            break;
        
        default:
            break;
        }

        std::cout << "\n";

        char inputtedAction[50];
        std::cout << "Please insert next action\n";
        std::cin >> inputtedAction;
        inputCharCounter = 0;
        char inputChar;
        while (inputtedAction[inputCharCounter]) {
            inputChar = inputtedAction[inputCharCounter];
            inputtedAction[inputCharCounter] = tolower(inputChar);
            inputCharCounter++;
        }

        nextState = mapStateToActions[currentState][actionToString[inputtedAction]];

        if (currentState == win) {
            if (strcmp(inputtedAction, "play") == 0) {
                currentState = nextState;
            } else if (strcmp(inputtedAction, "end") == 0) {
                std::cout << "Thank you for playing, Good Bye\n";
                exit(0);
            } else {
                std::cout << "ERROR!\n";
            }
        } else if (nextState) {
            currentState = nextState;
        } else { // not correct action
            std::cout << "ERROR!\n";
        }
    }
};