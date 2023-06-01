/*
 * card.h
 * Written by: Dave Lillethun
 * Edited by: Richard Townsend
 * Date: 11/8/2022
 * Purpose: Define a Card class to represent cards in the Rack-O game.
 *
 */
#ifndef _CARD_H
#define _CARD_H

#include <string>
using namespace std;

class Card {
public:
    // Constructor
    Card(int cardNumber);

    // Getter
    int getNum();

    // Drawing functions
    string toString();
    string getTopEdge();
    string getBlankLine();
    string getNumberLine();
    string getBottomEdge();

private:
    // The number on the card
    int cardNum;
};

#endif // _CARD_H
