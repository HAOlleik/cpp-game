#include <string.h>

#include "GameEngine.h"
#include "Drivers.h"

using namespace std;

void testGameEngineStates()
{
    GameEngine newGame;
    State nextState;

    while (true)
    {
        cout << newGame;

        char inputtedAction[50];
        cout << "Please insert next action\n";
        cin >> inputtedAction;
        inputToLower(inputtedAction);

        nextState = mapStateToActions[*(newGame.getState())][actionToString[inputtedAction]];

        if ((*(newGame.getState()) == win) & (strcmp(inputtedAction, "end") == 0))
        {
            cout << "Thank you for playing, Good Bye\n";
            exit(0);
        }

        if (nextState)
        {
            newGame.setState(&nextState);
        }
        else
        {
            cout << "ERROR!\n";
        }
    }
};
