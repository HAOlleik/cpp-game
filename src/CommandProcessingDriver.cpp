#include "CommandProcessing.h"
#include "Drivers.h"

void testCommandProcessor() {
    CommandProcessor commandProcessor;
    commandProcessor.getCommand(STATE::win);
    commandProcessor.getCommand(STATE::win);
    cout << commandProcessor;

    FileCommandProcessorAdapter fileCommandProcessor("src/testFiles/commandProcessor.txt");
    fileCommandProcessor.getCommand(STATE::start);
    fileCommandProcessor.getCommand(STATE::start);
    fileCommandProcessor.getCommand(STATE::map_loaded);
    fileCommandProcessor.getCommand(STATE::map_validated);
    cout << fileCommandProcessor;

    // for saveEffect it should be called on execution
    // executing here manually to show it works

    // mapStateToActions[State::win][actionToString[inputtedAction]];
}
