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

void testCards()
{
    Deck testDeck = Deck(10);
    testDeck.fillDeck();
    OrdersList testOrdersList = OrdersList();
    
    cout << "\n\n********Deck before playing********: " << endl << testDeck <<endl;

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

    cout <<"\n********All cards have been drawn from the deck********"<<endl;
    cout << "The addressses of the cards drawn from the deck are: " << endl << c1 << endl << c2 << endl << c3 << endl << c4 << endl << c5 << endl << c6 << endl << c7 << endl << c8 << endl << c9 << endl << c10 << endl;


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

    cout <<"\n********All cards have now been added to the hand********\n" <<"This results in a hand of: " << endl << testHand << endl;
    cout <<"With a deck that is now: " << endl << testDeck << endl;

    cout <<"\n********Cards will now be played one by one********" << endl;

    testHand.play(1, testDeck, testOrdersList);
    testHand.play(1, testDeck, testOrdersList);
    testHand.play(1, testDeck, testOrdersList);
    testHand.play(1, testDeck, testOrdersList);
    testHand.play(1, testDeck, testOrdersList);
    testHand.play(1, testDeck, testOrdersList);
    testHand.play(1, testDeck, testOrdersList);
    testHand.play(1, testDeck, testOrdersList);
    testHand.play(1, testDeck, testOrdersList);
    testHand.play(1, testDeck, testOrdersList);

    cout <<"\n********All cards have now been played********\n" << "Deck after playing all the cards:\n" << testDeck << endl;
    cout <<"Player hand after playing all the cards: " << testHand << endl;
}
