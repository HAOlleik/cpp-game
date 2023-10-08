#ifndef CARD_H
#define CARD_H
#include <iostream>
    using std::ostream;
#include <string>
    using std::string;
#include <vector>
    using std::vector;
#include "Order.h"

// forward declarations
class Player;

class Card
{
    private:
        Player *_player;

    protected:
        int cardID;
        string cardType;

    public:
        Card(); //default constructor
        Card(const Card &c); //copy constructor
        Card(int cardNum); //constructor 
        Card& operator = (const Card &c); //assignment operator overload
        //no destructor since Card does not use instance variables of other classes

        friend ostream& operator<<(ostream& os, const Card& card); //insertion stream operator

        string getCardType();
        int getCardID();

        //void play(Player &p);
        //bool validate();
};

class Deck
{
    protected:
        vector <Card*> deckVector; //vector of pointers to objects of type Card
        int sizeOfDeck;

    public:
        Deck(); //default constructor
        Deck(const Deck &d); //copy constructor
        Deck(int numOfCards); //constructor
        ~Deck(); //destructor
        Deck& operator = (const Deck &d); //assignment operator overload

        friend ostream& operator<<(ostream& os, const Deck& deck); //insertion stream operator

        Card* draw();
        void fillDeck();
        void addCardBackToDeck(int cardID);
        int getDeckSize();
        vector<Card*> getDeck() const;
        void setDeck(vector<Card*>);

};

class Hand
{
    protected:
        vector <Card*> playHand;

    public:
        Hand(); //default constructor
        Hand(const Hand &h); //copy constructor
        Hand& operator = (const Hand &h); //assignment operator overload
        ~Hand(); //destructor

        friend ostream& operator<<(ostream& os, const Hand& hand); //insertion stream operator

        int getHandSize();
        vector <Card*> getPlayHand() const;
        void addCard(Card& myCard);
        void printPlayHand();
        void play(int index, Deck& deck, OrdersList& OrdersList);
        void removeCard(int index);
};


class BombCard : public Card
{
};

class ReinforcementCard : public Card
{
};

class BlockadeCard : public Card
{
};

class AirliftCard : public Card
{
};

class DiplomacyCard : public Card
{
};

ostream &
operator<<(ostream &os, Card &c);

#endif