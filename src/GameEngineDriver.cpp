#include <string.h>

#include "GameEngine.h"
#include "Drivers.h"

using namespace std;

void testGameEngineStates()
{
    GameEngine newGame;
    STATE nextState;

    while (true)
    {
        cout << newGame;

        char inputtedAction[50];
        cout << "Please insert next action\n";
        cin >> inputtedAction;
        inputToLower(inputtedAction);

        if ((*(newGame.getState()) == win) & (strcmp(inputtedAction, "end") == 0))
        {
            cout << "Thank you for playing, Good Bye\n";
            break;
        }

        if (actionToString[inputtedAction] != 0 && mapStateToActions[*(newGame.getState())][actionToString[inputtedAction]] != 0)
        {
            nextState = mapStateToActions[*(newGame.getState())][actionToString[inputtedAction]];
        }
        else
        {
            cout << "Error! Please insert proper action\n\n";
            continue;
        }

        newGame.setState(&nextState);
    }
};
