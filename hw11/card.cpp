/*
* card.cpp
* Written by: Luke Randolph
* First edited on: April 21, 2023
* Purpose: Defines the functions of the card class for our game
*/
#include "card.h"
#include <iostream>

using namespace std;

/* Card
* Input: an integer, a string, a pointer to an integer, a chararcter
* Description: Sets ups a card with specified values, the card constructor
* Output: None
*/
Card::Card(int prestige, string color, int *gprice, char row){
    cardPrestige = prestige;
    gemColor = color;
    for (int i = 0; i < 5; i++){
        gemPrice[i]= gprice[i];
    }
    rowNum = row;
}

/* getPrestige
* Input: None
* Description: returns the prestige value of a card
* Output: an integer value
*/
int Card::getPrestige(){
    if(cardPrestige < 0){
        cerr << "ERROR: tried to read an uninitialized card" << endl;
        exit(EXIT_FAILURE);
    }
    return cardPrestige;
}

/* getGemColor
* Input: None
* Description: returns the discount color that a card has
* Output: a string
*/
string Card::getGemColor(){
    if(gemColor != "pink" && gemColor != "blue" && gemColor != "red" && 
       gemColor != "green" && gemColor != "white"){
        cerr << "ERROR: tried to read an uninitialized card" << endl;
        exit(EXIT_FAILURE);
    }
    return gemColor;
}

/* getPrice
* Input: an integer
* Description: returns the price of a specific color for a card
* Output: an integer value
*/
int Card::getPrice(int color){
    for (int i = 0; i < 5; i++){
        if(gemPrice[i] < 0){
            cerr << "ERROR: tried to read an uninitialized card" << endl;
            exit(EXIT_FAILURE);
        }
    }
    return gemPrice[color];
}

/* getRow
* Input: None
* Description: returns the row number/type of a card
* Output: a character value
*/
char Card::getRow(){
    if(rowNum != 'm' && rowNum != 'v' && rowNum != 'r' && rowNum != 't'){
        cerr << "ERROR: tried to read an uninitialized card" << endl;
        exit(EXIT_FAILURE);
    }
    return rowNum;
}