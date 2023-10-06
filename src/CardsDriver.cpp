/*THIS IS PURELY TEST CODE FOR THE TIME BEING*/

#include <iostream>
#include <vector>
#include "Cards.h"

using std::cout;

int main() {
    Hand myHand;
    Card card1(1); // Create a card
    Card card2(2); // Create another card
    myHand.addCard(card1); // Add cards to the hand
    myHand.addCard(card2);

    cout << myHand << std::endl; // This will call the custom operator<< for Hand
    return 0;
}