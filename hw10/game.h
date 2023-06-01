/*
 * game.h
 * Written by: Dave Lillethun
 * Edited by: Richard Townsend
 * Date: 11/9/2022
 * Purpose: Define a class to represent the rack-o game itself.
 *
 */
#ifndef _GAME_H
#define _GAME_H

#include "deck.h"
#include "discard_pile.h"
#include "hand.h"
#include <string>

using namespace std;

class Game {
public:
    const static int NUM_PLAYERS = 2;

    // Constructor
    Game(string deckFileName);
    // Destructor
    ~Game();

    void play();

private:
    void takeTurn(int playerNum);
    void takeDiscard(int playerNum);
    void drawFromDeck(int playerNum);
    bool didPlayerWin(int playerNum);

    // A rack-o game consists of a deck, a discard pile, and two hands of cards
    // (one for each player).
    Deck *deck;
    DiscardPile *discard;
    Hand *hands[NUM_PLAYERS];
};

#endif // _GAME_H
