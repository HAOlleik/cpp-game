#include "CommandProcessing.h"
#include "Drivers.h"

void testCommandProcessor() {
    CommandProcessor commandProcessor;
    commandProcessor.getCommand(State::win);
    commandProcessor.getCommand(State::win);
    cout << commandProcessor;

    FileCommandProcessorAdapter fileCommandProcessor("src/testFiles/commandProcessor.txt");
    fileCommandProcessor.getCommand(State::start);
    fileCommandProcessor.getCommand(State::start);
    fileCommandProcessor.getCommand(State::map_loaded);
    fileCommandProcessor.getCommand(State::map_validated);
    cout << fileCommandProcessor;

    // for saveEffect it should be called on execution
    // executing here manually to show it works

    // mapStateToActions[State::win][actionToString[inputtedAction]];
}
