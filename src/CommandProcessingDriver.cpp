#include "CommandProcessing.h"
#include "Drivers.h"

void testCommandProcessor() {
    CommandProcessor *commandProcessor = new CommandProcessor();
    commandProcessor->getCommand(STATE::win);
    commandProcessor->getCommand(STATE::win);
    cout << *commandProcessor;
}

void testCommandProcessor(string fileName) {
    FileCommandProcessorAdapter fileCommandProcessor(fileName);
    fileCommandProcessor.getCommand(STATE::start);
    fileCommandProcessor.getCommand(STATE::start);
    fileCommandProcessor.getCommand(STATE::map_loaded);
    fileCommandProcessor.getCommand(STATE::map_validated);
    cout << fileCommandProcessor;
}


    // for saveEffect it should be called on execution and gameEngine is handling it.
