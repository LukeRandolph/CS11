/*
* player.h
* Written by: Luke Randolph
* First edited on: April 21, 2023
* Purpose: Defines a player class for our game
*/
#ifndef _PLAYER_H
#define _PLAYER_H
#include <string>
#include "deck.h"
#include "vector.h"

using namespace std;

class Player{
public:
    Player();
    ~Player();
    //getters
    int totalPrestige();
    int getDiscount(int index);
    int getgemCount(int index);
    int gettotalGems();
    int getPurchases();
    Card *getReserve(int index);
    //setters
    void setGemCount(int color, int number);
    void setReserve(int index, Card *movingCard);
    void setDiscount(int index);
    void setPrestige(int num);
    void setPurchases();

private:
    int purchases;
    int prestigeCount;
    int discounts[5];
    int gemCount[6];
    Card *reserve[3];
};

#endif