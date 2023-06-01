/*
 * deck.cpp
 * Written by: Dave Lillethun
 * Edited by: Richard Townsend
 * Date last edited for starter code: 11/8/2022
 * Edited for HW10 by: {Luke Randolph}
 * Date: {April 14, 2023}
 * Purpose: Implement the methods for the Deck class in the Rack-O game.
 *
 */

#include "deck.h"
#include <fstream>
#include <iostream>

using namespace std;

// Constructor: read in the numbers listed in a "deck file", create a Card on
// the heap for each number, and store the resulting Card pointers in the deck.
Deck::Deck(string deckFileName)
{
    ifstream deckFile(deckFileName);
    if (deckFile.fail()) {
        cerr << "Failed to open deck file: " << deckFileName << endl;
        exit(EXIT_FAILURE);
    }

    // Read in all the numbers from the file, making a card for each one and
    // stroring it in the deck array.
    int cardNum;
    for (int i = 0; i < MAX_DECK_SIZE; i++) {
        // Read in the next number, making sure we didn't run into any errors
        deckFile >> cardNum;
        if (deckFile.eof()) {
            cerr << "File does not contain " << MAX_DECK_SIZE << " cards!"
                 << endl;
            exit(EXIT_FAILURE);
        } else if (deckFile.fail()) {
            cerr << "Failed to read from file: " << deckFileName << endl;
            exit(EXIT_FAILURE);
        }

        // Allocate a new Card object on the heap, and store a pointer to that
        // Card in the ith slot of "deck".
        deck[i] = new Card(cardNum);
    }

    // No cards have been drawn, so the top card of the deck is captured with
    // the Card pointer at index 0 of "deck".
    topCard = 0;
}

// Destructor: deallocate any Card pointers remaining in the deck
Deck::~Deck()
{
    for (int i = topCard; i < MAX_DECK_SIZE; i++) {
        delete deck[i];
    }
}

/* isEmpty
* Input: None
* Description: Checks if the deck is empty, i.e. all cards have been drawn
* Output: True if empty, false if not
*/
bool Deck::isEmpty()
{
    if (topCard == MAX_DECK_SIZE){
        return true;
    }else{
    return false;
    }
}

/* draw
* Input: None
* Description: Checks if the deck is empty. If it is not, then a new pointer is
* made to the top card of the deck and returned, and the index of topCard is 
* then updated by 1
* Output: Returns a pointer to the top card of the deck
*/
Card *Deck::draw()
{
    //check if empty for tie
    if (isEmpty()) {
        cout << "The deck is empty. IT'S A TIE!" << endl;
        exit(EXIT_FAILURE);
    }
    //initialize a new pointer to the current top card
    Card *drawn_Card = deck[topCard];
    //update topCard
    topCard++; 
    //return our pointer
    return drawn_Card;
}
