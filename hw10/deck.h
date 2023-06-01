/*
 * deck.h
 * Written by: Dave Lillethun
 * Edited by: Richard Townsend
 * Date: 11/8/2022
 * Purpose: Define a Deck class to represent a deck of cards in the
 *          Rack-O game.
 *
 */
#ifndef _DECK_H
#define _DECK_H

//NOTE: If we want to include a file we wrote, we need to use "" instead of <>
//when naming the file to include.
#include "card.h"
#include <string>

using namespace std;

class Deck {
public:
    const static int MAX_DECK_SIZE = 60;

    // Constructor
    Deck(string deckFileName);
    // Destructor
    ~Deck();

    bool isEmpty();
    Card *draw();

private:
    // The index of the top card in "deck"
    int topCard;
    // The cards in the deck (each represented with a Card pointer)
    Card *deck[MAX_DECK_SIZE];
};

#endif // _DECK_H
