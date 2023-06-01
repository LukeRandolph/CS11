/*
* deck.h
* Written by: Luke Randolph
* First edited on: April 21, 2023
* Purpose: Defines a deck class for our game
*/

#ifndef _DECK_H
#define _DECK_H

#include "card.h"
#include "vector.h"
#include <string>

using namespace std;


class Deck{
public:
    //constructor
    Deck();
    //necessary for deck/vector formatting
    void setupDeck(string filename, char type);
    //destructor
    ~Deck();
    bool empty();
    Card *draw();
    Card *at(int index);
    int getdeckSize();
    void setdeckSize(int num);

private:
    int capacity;
    char type; 
    int deckSize;    //We can't use the same name as the size() method above!
    Data *buffer;
    //needed for deck/vector formatting
    Vector deck;
    int draw_count;
};

#endif