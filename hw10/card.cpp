/*
 * card.cpp
 * Written by: Dave Lillethun
 * Edited by: Richard Townsend
 * Date last edited for starter code: 11/8/2022
 * Edited for HW10 by: {Luke Randolph}
 * Date: {April 13, 2023}
 * Purpose: Implement the methods for the Card class in the Rack-O game.
 *
 */

//NOTE: If we want to include a file we wrote, we need to use "" instead of <>
//when naming the file to include.
#include "card.h"
#include <iostream>

using namespace std;

// Constructor: initialize the private field of a Card object
Card::Card(int cardNumber)
{
    cardNum = cardNumber;
}

// getNum
// Input: none
// Description: Getter for the cardNum private field
// Output: the number on this card
int Card::getNum()
{
    if (cardNum < 0) {
        cerr << "ERROR: tried to read an uninitialized card" << endl;
        exit(EXIT_FAILURE);
    }
    return cardNum;
}

/*
 * Everything below this comment is purely for "drawing" cards on the screen.
 * Students won't need to read through or modify any of these methods.
 *
 */

string Card::toString()
{
    if (cardNum < 0) {
        cerr << "ERROR: tried to read an uninitialized card" << endl;
        exit(EXIT_FAILURE);
    }

    return getTopEdge() + '\n' + getBlankLine() + '\n' + getNumberLine() +
           '\n' + getBlankLine() + '\n' + getBottomEdge() + '\n';
}

string Card::getTopEdge()
{
    if (cardNum < 0) {
        cerr << "ERROR: tried to read an uninitialized card" << endl;
        exit(EXIT_FAILURE);
    }
    return "/----\\";
}

string Card::getBlankLine()
{
    if (cardNum < 0) {
        cerr << "ERROR: tried to read an uninitialized card" << endl;
        exit(EXIT_FAILURE);
    }
    return "|    |";
}

string Card::getNumberLine()
{
    if (cardNum < 0) {
        cerr << "ERROR: tried to read an uninitialized card" << endl;
        exit(EXIT_FAILURE);
    }

    string numberLine = "";
    numberLine += "| ";
    if (cardNum < 10) {
        numberLine += ' ';
    }
    numberLine += to_string(cardNum); // From the string library
    numberLine += " |";
    return numberLine;
}

string Card::getBottomEdge()
{
    if (cardNum < 0) {
        cerr << "ERROR: tried to read an uninitialized card" << endl;
        exit(EXIT_FAILURE);
    }
    return "\\----/";
}
