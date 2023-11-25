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

void testCommandProcessor(vector<string> arguments, size_t size) {
    cout << "\n testCommandProcessor running \n\n";
    bool optionProvided = false;
    for (size_t i = 1; i < size; ++i) {
        optionProvided = true;
        if (arguments[i] == "-console" || arguments[i] == "--c") {
            testCommandProcessor();
        } else if (arguments[i] == "-file" || arguments[i] == "--f") {
            string filename = arguments[i + 1];
            if (filename.empty()) {
                std::cerr << "Error: No filename provided for file mode. Usage: -file <filename> or --f <filename>" << std::endl;
                exit(1);
            }
            testCommandProcessor(filename);
        } else {
            cout << "Please provide a proper input" <<endl;
            exit(1);
        }
    }

    if (!optionProvided) {
        cout << "Using default option: Console (-console, --c)\n";
        testCommandProcessor();
    }
}

    // for saveEffect it should be called on execution and gameEngine is handling it.
