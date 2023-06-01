/*
 * hand.h
 * Written by: Dave Lillethun
 * Edited by: Richard Townsend
 * Date: 11/8/2022
 * Purpose: Define a Hand class to represent a player's hand in the Rack-O game.
 *
 */
#ifndef _HAND_H
#define _HAND_H

#include "card.h"

class Hand {
public:
    const static int HAND_SIZE = 5;

    // Constructor
    Hand(Card *c1, Card *c2, Card *c3, Card *c4, Card *c5);
    // Destructor
    ~Hand();

    bool isWinningHand();
    Card *replaceCard(Card *newCard);

    void print();

private:
    // The cards in the player's hand (each represented with a Card pointer)
    Card *cards[HAND_SIZE];
};

#endif // _HAND_H
