/*
* player.cpp
* Written by: Luke Randolph
* First edited on: April 21, 2023
* Purpose: Defines the functions of the player class for our game
*/

#include "player.h"
#include "card.h"
#include <string>
#include <iostream>

/* Player
* Input: none
* Description: Player constructor
* Output: none
*/
Player::Player() {
    prestigeCount = 0;
    purchases = 0;
    for (int i = 0; i < 5; i++) {
        gemCount[i] = 0;
        discounts[i] = 0;
    }
    gemCount[5] = 0;
    for (int i = 0; i < 3; i++) {
        reserve[i] = nullptr;
    }
}

/* ~Player
* Input: none
* Description: Player destructor
* Output: none
*/
Player::~Player() {
    for (int i = 0; i < 3; i++) {
        if (reserve[i] != nullptr) {
            delete reserve[i];
        }
    }
}

/* totalPrestige
* Input: None
* Description: returns the prestige count of a player
* Output: an integer value
*/
int Player::totalPrestige(){
    return prestigeCount;
}

/* getDiscount
* Input: an integer
* Description: returns the discount count of a player at a particular index
* Output: an integer from an array
*/
int Player::getDiscount(int index){
    return discounts[index];
}

/* getgemCount
* Input: an integer
* Description: returns the gemCount count of a player at a particular index
* Output: an integer value from an array
*/
int Player::getgemCount(int index){
    return gemCount[index];
}

/* Card *getReserve
* Input: an integer
* Description: returns the reserve count of a player at a particular index
* Output: a card pointer
*/
Card *Player::getReserve(int index){
    return reserve[index];
}

/* setReserve
* Input: an integer, and a card pointer
* Description: sets the reserve count of a player at a particular index
* with a passed in card pointer
* Output: none
*/
void Player::setReserve(int index, Card *movingCard){
    reserve[index] = movingCard;
}

/* setGemCount
* Input: two integers
* Description: adds an inputted number value to the gem count 
* of a player at an inputted index equal 
* Output: none
*/
void Player::setGemCount(int color, int number){
    gemCount[color] += number;
}

/* gettotalGems
* Input: None
* Description: returns the total amount of gems of a player
* Output: an integer value
*/
int Player::gettotalGems(){
    int totalGems = 0;
    for(int i = 0; i < 6; i++){
        int num = getgemCount(i);
        totalGems += num;
    }
    return totalGems;
}

/* setDiscount
* Input: an integer
* Description: adds 1 to the discount value of a specified color of a player
* Output: none
*/
void Player::setDiscount(int index){
    discounts[index] += 1;
}

/* setPrestige
* Input: an integer
* Description: adds an inputted value number to the prestige count of a player
* Output: none
*/
void Player::setPrestige(int num){
    prestigeCount += num;
}

/* setPurchases
* Input: None
* Description: adds 1 to the purchases value for a player
* Output: none
*/
void Player::setPurchases(){
    purchases++;
}

/* getPurchases
* Input: None
* Description: returns the amount of purchases a player has done
* Output: an integer value
*/
int Player::getPurchases(){
    return purchases;
}


