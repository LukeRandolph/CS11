/*
* deck.cpp
* Written by: Luke Randolph
* First edited on: April 21, 2023
* Purpose: Defines the functions of the deck class for our game
*/

#include "deck.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
//constructor for private part of game class
Deck::Deck(){
}

/* setupDeck
* Input: a file and a character
* Description: fills in a deck from an inputted file with cards of a specified
* type
* Output: none
*/
void Deck::setupDeck(string filename, char type){
    ifstream infile(filename);
    if(infile.fail()){
        cerr << "Failed to open deck file" << filename << endl;
        exit(EXIT_FAILURE);
    }
    this->type = type;
    char row;
    int cardPrestige, white, red, blue, green, pink;
    string gemColor, skip;
    draw_count = 0;
    //need to skip over first line of strings when reading in
    for(int i = 0; i < 8; i++){
        infile >> skip;
    }
    while(!infile.eof()){
        infile >> row >> cardPrestige >> gemColor >> white >> red >> pink 
        >> blue >> green;
        int gemPrice[5];
        gemPrice[0] = white;
        gemPrice[1] = red;
        gemPrice[2] = pink;
        gemPrice[3] = blue;
        gemPrice[4] = green;
        //if conditional to only make cards of the desired type
        if(type == row){
            deck.push_back(new Card(cardPrestige, gemColor, gemPrice, row));
        }
    }
    infile.close();
}

//deck destructor
Deck::~Deck(){
    
}

/* empty
* Input: None
* Description: returns true if a deck is empty
* Output: true/false
*/
bool Deck::empty() {
  if (type == 'm'){
    if (draw_count == 40) {
        return true;
    }
  } else if (type == 't'){
    if (draw_count == 30) {
        return true;
    }
  } else if (type == 'v'){
    if (draw_count == 20) {
        return true;
    }
  } else {
    if (draw_count == 10) {
        return true;
    }
  }
  return false; 
}

/* Card *draw
* Input: None
* Description: checks if a deck is empty, and if not makes a new card pointer to
* the card at the back of a deck, then pops back on the deck and returns the
* card pointer
* Output: a pointer to a card
*/
Card *Deck::draw(){
    if (empty()) {
        cerr << "ERROR: Drawing from an empty deck" << endl;
        exit(EXIT_FAILURE);
    }
    Card *drawnCard = deck.back();
    deck.pop_back();
    return drawnCard;
}

/* Card *at
* Input: an integer
* Description: uses vector notation to return the point in the deck 
* at a specified index
* Output: a specified spot in a deck
*/
Card *Deck::at(int index) {
    return deck.at(index);
} 

/* getdeckSize
* Input: None
* Description: returns the current size of a deck
* Output: an integer value
*/
int Deck::getdeckSize(){
    return deck.size();
}

/* setdeckSize
* Input: an integer
* Description: sets the deck size equal to a specified number
* Output: none
*/
void Deck::setdeckSize(int num){
    deckSize = num;
}