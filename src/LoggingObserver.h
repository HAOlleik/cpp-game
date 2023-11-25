#pragma once

#include <iostream>
    using std::ostream;
#include <string>
    using std::string;
#include <vector>
    using std::vector;
#include <fstream>
    using std::ofstream;
#include <list>
    using std::list;

//inherited by all classes
class ILoggable{
    public:
        virtual string stringToLog() = 0;//= 0 denotes that it is a pure virtual function
};

class Observer{
    public:
        ~Observer(); //destructor
        Observer(); //constructor
        virtual void update(ILoggable* iloggable) = 0;
};

class Subject{
    public:
        ~Subject(); //destructor
        Subject(); //constructor
        virtual void attachObserver(Observer* observer);
        virtual void detachObserver(Observer* observer);
        virtual void notify(ILoggable* iloggable);

    private:
        list<Observer*> *_observerList;
};

class LogObserver: public Observer{
    public:
        ~LogObserver(); //destructor
        LogObserver(); //constructor
        void update(ILoggable* ilogabble);//implements from Observer class it inherits
        ofstream* getFile();

    private:
        ofstream* file;
};

void testLoggingObserver();