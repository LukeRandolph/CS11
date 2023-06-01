/*
 * discard_pile.h
 * Written by: Dave Lillethun
 * Edited by: Richard Townsend
 * Date: 11/9/2022
 * Purpose: Define a class to represent the discard pile in the Rack-O game.
 *
 */
#ifndef _DISCARD_PILE_H
#define _DISCARD_PILE_H

#include "card.h"

class DiscardPile {
public:
    // Constructor
    DiscardPile(Card *seedCard);
    // Destructor
    ~DiscardPile();

    void discard(Card *discard);
    Card *takeDiscard();

    void print();

private:
    // The only card in the discard pile that matters (and can be accessed) is the
    // top card.
    Card *topDiscard;
};

#endif // _DISCARD_PILE_H
