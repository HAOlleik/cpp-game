#include "Cards.h"
#include "Player.h"
#include "Order.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;


/*
    ----------------------------
    Card class
    ----------------------------
*/

//default constructor
Card::Card()
{
    cardID = 0;
    cardType ="";
}

//copy constructor
Card::Card(const Card &c)
{
    (*this).cardID = c.cardID;
    (*this).cardType = c.cardType;
}

//constructor to create new card and assign its cardType
Card::Card(int cardNum)
{
    cardID = cardNum;
    cardType = "";

    switch (cardID)
    {
        case 1:
            cardType = "bomb";
            break;
        case 2:
            cardType = "reinforcement";
            break;
        case 3:
            cardType = "blockade";
            break;
        case 4:
            cardType = "airlift";
            break;
        case 5:
            cardType = "diplomacy";
            break;
    }       
}

//assignment operator overload
Card &Card::operator = (const Card &c)
{
    (*this).cardID = c.cardID;
    (*this).cardType = c.cardType;
    return *this;
}

//insertion stream operator
ostream& operator<<(ostream& os, const Card& card) 
{
    os << "Card ID: " << card.cardID << ", Card Type: " << card.cardType << endl;
    return os;
}

//cardID getter
int Card::getCardID()
{
    return cardID;
}

//cardType getter
string Card::getCardType()
{
    return cardType;
}


/*
    ----------------------------
    Deck Class
    ----------------------------
*/

//default constructor
Deck::Deck()
{
    deckVector = vector<Card *>(); //deck is empty vector of pointers to objects of type Card
}

//copy constructor
Deck::Deck(const Deck &d)
{
    //pointer to cards in original deck to populate the copy deck with the original deck's cards
    for (int i = 0; i < d.deckVector.size(); i++)
    {
       (*this).deckVector.push_back(new Card(*(d.deckVector[i])));
    }
}

//constructor with number of cards
Deck::Deck(int numOfCards)
{
    sizeOfDeck = numOfCards;
    deckVector = vector<Card*>();
}

//assignment operator overload
Deck &Deck::operator = (const Deck &d)
{
    (*this).sizeOfDeck = int(d.sizeOfDeck);

    for (int i = 0; i < d.deckVector.size(); i++)
    {
       (*this).deckVector.push_back(new Card(*(d.deckVector[i])));
    }

    return *this;
}

int Deck::getDeckSize()
{
    return sizeOfDeck;
}

//return current deck (vector of pointers to card objects)
vector<Card*> Deck::getDeck() const{
    return deckVector;
}

//method to set deck 
void Deck::setDeck(vector<Card*>newDeck)
{
    this->deckVector = newDeck;
}

//generates new random Card and returns pointer to it
Card* Deck::draw()
{
    if (deckVector.size() >= 1)
    {
        int index = rand() % deckVector.size(); //random card in the deck, return value ranges from 0 to (deck size -1)
        Card* cardDrawn = *(deckVector.begin() + index);
        deckVector.erase(deckVector.begin() + index);
        sizeOfDeck -= 1;
        return cardDrawn;
    }
    else
    {
        cout <<"The deck is empty." << endl;
        return nullptr;
    }
}

//insertion stream operator
ostream& operator<<(ostream& os, const Deck& deck) 
{
    os << "Deck Size: " << deck.sizeOfDeck << "\n";

    os << "Cards in the Deck:\n";
    for (const Card* card : deck.deckVector) {
        os << *card << "\n"; // This will use the Card's custom operator<<
    }

    return os;
}

//method to fill deck with cards randomly
void Deck::fillDeck()
{
    for (int i = 0; i < sizeOfDeck; i++)
    {
        int randomCardNum = rand() % 5 + 1; //random number between 1 and 5
        deckVector.push_back(new Card(randomCardNum));
    }
}

//method to return the played card back to the deck
void Deck::addCardBackToDeck(int cardID)
{
    Card* returnCard = new Card(cardID);
    vector<Card *> deckInstance = this->getDeck();
    deckInstance.push_back(returnCard);
    this->setDeck(deckInstance);
    cout << "The card of type " << returnCard->getCardType() << " has been returned to the deck." << endl;
}

//deck destructor
Deck::~Deck()
{
    for (int i = 0; i < deckVector.size(); i++)
    {
        delete deckVector[i];
        deckVector[i] = nullptr;
    }
}


/*
    ----------------------------
    Hand Class
    ----------------------------
*/

//default constructor
Hand::Hand()
{
    playHand = vector<Card*>();
}

//copy constructor
Hand::Hand(const Hand &h)
{
    for (int i = 0; i < h.playHand.size(); i++)
    {
        (*this).playHand.push_back(new Card(*(h.playHand[i])));
    }
}

//assignment operator overload
Hand &Hand::operator=(const Hand &h)
{
    for (int i = 0; i < (h.playHand.size()); i++)
    {
        (*this).playHand.push_back(new Card(*(h.playHand)[i]));
    }
    return *this;
}

//destructor
Hand::~Hand()
{
    for (int i = 0; i < playHand.size(); i++)
    {
        delete playHand[i];
        playHand[i] = nullptr;
    }
}

ostream& operator<<(ostream& os, const Hand& hand) //insertion stream operator
{
    os << "Hand Size: " << hand.playHand.size() << "\n";

    os << "Cards in the Hand:\n";
    for (const Card* card : hand.playHand) {
        os << *card << "\n"; // This will use the Card's custom operator<<
    }

    return os;
}

vector<Card*> Hand::getPlayHand() const
{
    return playHand;
}

int Hand::getHandSize()
{
    return playHand.size();
}

void Hand::addCard(Card& myCard)
{
    playHand.push_back(&myCard);
}

void Hand::removeCard(int index)
{
    if (index >= 0 && index <= playHand.size())
    {
        playHand.erase(playHand.begin() + index);
    }
    else
    {
        cout << "Index out of bounds." << endl;
    }
}

void Hand::play(int index, Deck &deck, Player& player)
{
    index -= 1;
    int orderCard = (playHand[index]->getCardID());

    // DeployOrder* d = new DeployOrder;
    // AdvanceOrder* a = new AdvanceOrder;
    // BombOrder* b = new BombOrder;
    // BlockadeOrder* bd = new BlockadeOrder;
    // AirliftOrder* al = new AirliftOrder;
    // NegotiateOrder* n = new NegotiateOrder;

    // switch (orderCard)
    // {

    // }
}