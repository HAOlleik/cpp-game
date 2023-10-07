#include <iostream>
#include <vector>
#include "Cards.h"
#include "Player.h"

using std::cout;
using std::endl;

/*
    ----------------------------
    Free Function for Cards
    ----------------------------
*/

int main()
{
    Deck testDeck = Deck(10);
    testDeck.fillDeck();
    
    cout << "Deck before playing: " << endl << testDeck <<endl;

    Card* c1 = testDeck.draw();
    Card* c2 = testDeck.draw();
    Card* c3 = testDeck.draw();
    Card* c4 = testDeck.draw();
    Card* c5 = testDeck.draw();
    Card* c6 = testDeck.draw();
    Card* c7 = testDeck.draw();
    Card* c8 = testDeck.draw();
    Card* c9 = testDeck.draw();
    Card* c10 = testDeck.draw();

    cout << "The addressses of the cards drawn from the deck are: " << endl << c1 << c2 << c3 << c4 << c5 << c6 << c7 << c8 << c9 << c10 << endl;


    Hand testHand;
    testHand.addCard(*c1);
    testHand.addCard(*c2);
    testHand.addCard(*c3);
    testHand.addCard(*c4);
    testHand.addCard(*c5);
    testHand.addCard(*c6);
    testHand.addCard(*c7);
    testHand.addCard(*c8);
    testHand.addCard(*c9);
    testHand.addCard(*c10);

    cout <<"This results in a hand of: " << endl << testHand << endl;
    cout <<"With a deck that is now: " << endl << testDeck << endl;

    /*Play method still needs to be implemented*/
}
