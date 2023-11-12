#include <iostream>
    using std::endl;
    using std::cout;
#include <string>
    using std::string;
#include <vector>
    using std::vector;
#include <tuple>
    using std::tuple;
    using std::get;
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

Observer::~Observer(){

}

Observer::Observer(){
    
}

//destructor closes the io and deletes the file variable
LogObserver::~LogObserver(){
    getFile()->close();
    delete this->file;
}

LogObserver::LogObserver(){
    file = new std::ofstream("Logfile.txt");
}

//value from stringToLog() being written to output file when update is called
void LogObserver::update(ILoggable* iloggable){
    *file<<iloggable->stringToLog() <<endl;
}

ofstream* LogObserver::getFile(){
    return file;
}

//destructor deletes the observer list
Subject::~Subject(){
    delete _observerList;
}

Subject::Subject(){
    _observerList = new list<Observer*>;
}

void Subject::attachObserver(Observer* observer){
    _observerList->push_back(observer);
}

void Subject::detachObserver(Observer* observer){
    _observerList->remove(observer);
}

//all observers who are attached to the subject are updated
void Subject::notify(ILoggable* iloggable){
    list<Observer *>::iterator iterator = _observerList->begin();
    Subject* subject = this;
    string subjectType = typeid(*subject).name();
    for(; iterator != _observerList->end(); ++iterator){
        (*iterator)->update(iloggable);
    }
}

//TO IMPLEMENT
void testLoggingObserver(){
    GameEngine* myGameEngine = new GameEngine();
    
}