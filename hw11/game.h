/*
 * game.h
 * CS11 Splendor
 */

#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <fstream>
#include <string>
#include "termfuncs.h"
#include "deck.h"
#include "card.h"
#include "player.h"
#include "vector.h"
using namespace std;

class Game {
public:
    //constructor
    Game(string filename, string play_nobles);
    void setupGame();
    //destructor
    ~Game();
    //main gameplay
    void playGame();

    //utility functions
    string indexToColor(int index);

    void p_and_e(bool *game_over, bool player1_turn);
    void setGemBank(int color, int num);
    void takeTwoGems(bool *game_over, bool player1_turn, int playerNum);
    bool colorChecker(string color);
    void takeThreeGems(bool *game_over, bool player1_turn, int playerNum);
    bool gemChecker(string color);
    void reserveCard(bool *game_over, bool player1_turn, int playerNum);
    bool typeCheck(string type);
    void tenGems(int playerNum);
    bool columnCheck(string column, int *index);
    bool fullResCheck(int playerNum);
    Card *findGridCard(string type, int index);
    void SetReserve(int playerNum, string type, int index);
    void updateGrid(string type, int index);
    void addGoldGem(int playerNum);
    void buyCard(bool *game_over, bool player1_turn, int playerNum);
    bool validPurchase(string type, int index, int playerNum);
    int needGold(int playerNum, int j, int *goldGems, Card *Card, 
                 int usedGems[], int *spentGold);
    void resetGrid(string type, int index);
    void updateDiscounts(string type, int index, int playerNum);
    void updatePrestige(string type, int index, int playerNum);
    void buyReserveCard(bool *game_over, bool player1_turn, int playerNum);
    bool reserveCheck(string column, int *index);
    bool validRPurchase(int index, int playerNum);
    void End_Of_Game(int quit);

private:
    //drawing functions
    void drawBoard();
    void drawNoble(int vpos, int hpos, Card *c);
    void drawPlayer(int vpos, int hpos, Player *p);
    void drawDeck(int vpos, int hpos, string type);
    void drawCard(int vpos, int hpos, Card *c);
    void drawGem(int vpos, int hpos, string color);
    void clearBoard();

    static const int BOARD_HEIGHT = 41;
    static const int BOARD_WIDTH = 120;
    static const int CARD_WIDTH = 13;
    static const int CARD_HEIGHT = 8;
    static const int CARD_ROWS = 3;
    static const int CARD_COLS = 4;
    static const int NUM_NOBLES = 3;
    static const int GEMS = 6;

    //nobles activated true/false
    bool play_nobles;

    //cards in play
    Card *grid[CARD_ROWS][CARD_COLS];

    //display
    char board[BOARD_HEIGHT][BOARD_WIDTH];
    string board_color[BOARD_HEIGHT][BOARD_WIDTH];

    //Gem colors in the game
    string colors[GEMS];

    int gem_bank[6];

    Deck mines;
    Deck transport;
    Deck vendors;
    Deck nobles;

    Player *player[2];
};

#endif
