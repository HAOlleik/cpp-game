#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <tuple>
using std::get;
using std::tuple;
#include <fstream>
using std::ofstream;
#include <list>
using std::list;

#include "Cards.h"
#include "CommandProcessing.h"
#include "GameEngine.h"
#include "Map.h"
#include "Order.h"
#include "Player.h"
#include "LoggingObserver.h"

Observer::~Observer()
{
}

Observer::Observer()
{
}

// destructor closes the io and deletes the file variable
LogObserver::~LogObserver()
{
    getFile()->close();
    delete this->file;
}

LogObserver::LogObserver()
{
    file = new std::ofstream("Logfile.txt");
}

// value from stringToLog() being written to output file when update is called
void LogObserver::update(ILoggable *iloggable)
{
    *file << iloggable->stringToLog() << endl;
}

ofstream *LogObserver::getFile()
{
    return file;
}

// destructor deletes the observer list
Subject::~Subject()
{
    delete _observerList;
}

Subject::Subject()
{
    _observerList = new list<Observer *>;
}

void Subject::attachObserver(Observer *observer)
{
    _observerList->push_back(observer);
}

void Subject::detachObserver(Observer *observer)
{
    _observerList->remove(observer);
}

// all observers who are attached to the subject are updated
void Subject::notify(ILoggable *iloggable)
{
    list<Observer *>::iterator iterator = _observerList->begin();
    Subject *subject = this;
    string subjectType = typeid(*subject).name();
    for (; iterator != _observerList->end(); ++iterator)
    {
        (*iterator)->update(iloggable);
    }
}

// TO IMPLEMENT
void testLoggingObserver()
{
    GameEngine* myGameEngine = new GameEngine();
    Subject *engineSubject = new GameEngine();
    ILoggable *engineLoggable = new GameEngine();

    Command* myCommand = new Command();
    Subject* commandSubject = new Command();
    ILoggable* commandLoggable = new Command();

    CommandProcessor *myCommandProcessor = new CommandProcessor();
    Subject *commandProccessorSubject = new CommandProcessor();
    ILoggable *commandProccessorLoggable = new CommandProcessor();

    OrdersList *myOrdersList = new OrdersList();
    Subject *ordersListSubject = new OrdersList();
    ILoggable *ordersListLoggable = new OrdersList();

    Order *myOrder = new DeployOrder();
    Subject *orderSubject = new DeployOrder();
    ILoggable *orderLoggable = new DeployOrder();

    cout << "**************************************************************************" << endl;
    cout << "PART 5 TESTING" << endl;

    cout << "Demonstrating that The Command, CommandProcessor, Order, OrderList, and GameEngine "
         << "classes are all a subclass of the Subject and ILoggable classes" << endl;
    cout << "engineSubject type: " << typeid(engineSubject).name() << endl;
    cout << "engineLoggable type " << typeid(engineLoggable).name() << endl;

    cout << "commandProccessorSubject type: " << typeid(commandProccessorSubject).name() << endl;
    cout << "commandProccessorLoggable type " << typeid(commandProccessorLoggable).name() << endl;

    cout << "ordersListSubject type: " << typeid(ordersListSubject).name() << endl;
    cout << "ordersListLoggable type " << typeid(ordersListLoggable).name() << endl;

    cout << "orderSubject type: " << typeid(orderSubject).name() << endl;
    cout << "orderLoggable type " << typeid(orderLoggable).name() << endl;

    LogObserver* myLogObserver = new LogObserver();
    myGameEngine->attachObserver(myLogObserver);
    myCommand->attachObserver(myLogObserver);
    myCommandProcessor->attachObserver(myLogObserver);
    myOrder->attachObserver(myLogObserver);

    myGameEngine->setState(map_loaded);
    myCommand->saveEffect("testeffect");
    myCommandProcessor->getCommand(map_loaded);
    myOrdersList->addOrder(myOrder);
    myOrder->execute();

    cout << "Part 5 is done " << endl;
}