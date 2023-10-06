#include <string.h>

#include "GameEngine.h"

using namespace std;

void testGameEngineStates()
{
    GameEngine newGame;
    State nextState;

    while (true)
    {
        cout << "The current state is: ";
        switch (newGame.getState())
        {
        case 1:
            cout << "Start";
            break;
        case 2:
            cout << "Map Loaded";
            break;
        case 3:
            cout << "Map Validated";
            break;
        case 4:
            cout << "Players Added";
            break;
        case 5:
            cout << "Assign Reinforcement";
            break;
        case 6:
            cout << "Issue Orders";
            break;
        case 7:
            cout << "Execute Orders";
            break;
        case 8:
            cout << "Win";
            break;
        default:
            break;
        }

        cout << "\n";

        char inputtedAction[50];
        cout << "Please insert next action\n";
        cin >> inputtedAction;
        inputToLower(inputtedAction);

        nextState = mapStateToActions[newGame.getState()][actionToString[inputtedAction]];

        if (newGame.getState() == win & (strcmp(inputtedAction, "end") == 0))
        {
            cout << "Thank you for playing, Good Bye\n";
            exit(0);
        }

        if (nextState)
        {
            newGame.setState(nextState);
        }
        else
        {
            cout << "ERROR!\n";
        }
    }
};
