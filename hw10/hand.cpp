/*
 * hand.cpp
 * Written by: Dave Lillethun
 * Edited by: Richard Townsend
 * Date last edited for starter code: 11/8/2022
 * Edited for HW10 by: {Luke Randolph}
 * Date: {April 14, 2023}
 * Purpose: Implement the methods for the Hand class in the Rack-O game.
 *
 */
#include "card.h"
#include "hand.h"
#include <iostream>

using namespace std;

// Constructor: Store the provided card pointers in our hand.
Hand::Hand(Card *c1, Card *c2, Card *c3, Card *c4, Card *c5)
{
    cards[0] = c1;
    cards[1] = c2;
    cards[2] = c3;
    cards[3] = c4;
    cards[4] = c5;
}

// Destructor: Deallocate any cards in our hand
Hand::~Hand()
{
    for (int i = 0; i < HAND_SIZE; i++) {
        delete cards[i];
    }
}

/* isWinningHand
* Input: None
* Description: Checks if the cards in one's hand satisfy the win condition of 
* the game Rack-o
* Output: True if it does, false if not
*/
bool Hand::isWinningHand()
{
    int num1, num2, num3, num4, num5;
    //get the numbers on the cards in order of the hand
    num1 = cards[0]->getNum();
    num2 = cards[1]->getNum();
    num3 = cards[2]->getNum();
    num4 = cards[3]->getNum();
    num5 = cards[4]->getNum();
    //win condition
    if(num1 < num2 && num2 < num3 && num3 < num4 && num4 < num5){
        return true;
    }
    return false;
}

/* replaceCard
* Input: A pointer to a card
* Description: First, prints out a player's hand. Then prompts the player which
* card in their hand they want to replace. First, a new pointer is made to the
* card that is going to be discarded. Then it replaces the current card
* in the hand with the card passed into the function, and returns a pointer
* to the discarded card.
* Output: returns a pointer to the discarded card
*/
Card *Hand::replaceCard(Card *newCard)
{
    //first print player's hand
    print();
    cout << endl;
    int index;
    cout << "Enter the index of the card you'd like to discard: ";
    cin >> index;
    if (index < 0 || index > 4){
        cout << "Enter the index of the card you'd like to discard: ";
        cin >> index;
    }
    //pointer to discarded card
    Card *oldCard = cards[index];
    //update hand
    cards[index] = newCard;
    //return the pointer to the discarded card
    return oldCard;

}

/*
 * Everything below this comment is purely for "drawing" hands on the screen.
 * Students won't need to read through or modify any of these methods.
 *
 */
void Hand::print()
{
    for (int i = 0; i < HAND_SIZE; i++) {
        if (cards[i] == NULL) {
            cerr << "ERROR: hand does not have " << HAND_SIZE << " cards!"
                 << endl;
            exit(EXIT_FAILURE);
        }
    }

    // print Top Edge
    for (int i = 0; i < HAND_SIZE; i++) {
        if (i > 0) {
            cout << "  ";
        }
        cout << cards[i]->getTopEdge();
    }
    cout << endl;

    // print Blank Line
    for (int i = 0; i < HAND_SIZE; i++) {
        if (i > 0) {
            cout << "  ";
        }
        cout << cards[i]->getBlankLine();
    }
    cout << endl;

    // print Number Line
    for (int i = 0; i < HAND_SIZE; i++) {
        if (i > 0) {
            cout << "  ";
        }
        cout << cards[i]->getNumberLine();
    }
    cout << endl;

    // print Blank Line
    for (int i = 0; i < HAND_SIZE; i++) {
        if (i > 0) {
            cout << "  ";
        }
        cout << cards[i]->getBlankLine();
    }
    cout << endl;

    // print Bottom Edge
    for (int i = 0; i < HAND_SIZE; i++) {
        if (i > 0) {
            cout << "  ";
        }
        cout << cards[i]->getBottomEdge();
    }
    cout << endl;

    // print index numbers
    for (int i = 0; i < HAND_SIZE; i++) {
        cout << "   ";
        if (i > 0) {
            cout << "    ";
        }
        cout << i;
    }
    cout << endl;
}
