/*
* card.h
* Written by: Luke Randolph
* First edited on: April 21, 2023
* Purpose: Defines a card class for our game
*/

#ifndef _CARD_H
#define _CARD_H
#include <string>

using namespace std;

class Card{
public:
    //Card Constructor
    Card(int prestige, string color, int *gprice, char row);
    //Getters and Setters
    int getPrestige();
    string getGemColor();
    int getPrice(int color);
    char getRow();
private:
    int cardPrestige;
    string gemColor;
    int gemPrice[5];
    char rowNum;
};

#endif 
