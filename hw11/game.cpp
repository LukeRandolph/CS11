/*
 * game.cpp
 * CS11 Splendor
 */

#include "game.h"
#include <fstream>

/* Game
* Input: a file and a string
* Description: Game constructor
* Output: none
*/
Game::Game(string filename, string play_nobles){
    //store gem colors for easy reference in drawing functions
    colors[0] = "white";
    colors[1] = "red";
    colors[2] = "pink";
    colors[3] = "blue";
    colors[4] = "green";
    colors[5] = "gold";
    //include nobles or not
    if (play_nobles == "true") {
        this->play_nobles = true;
    } else {
        this->play_nobles = false;
    }
     //initialize the board
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            board[i][j] = ' ';
            board_color[i][j] = "white";
        }
    }
    //initialize our decks
    mines.setupDeck(filename, 'm');
    transport.setupDeck(filename, 't');
    vendors.setupDeck(filename, 'v');
    nobles.setupDeck(filename, 'n');
    setupGame();
}

/* setupGame
* Input: none
* Description: sets up the game with the grid and gembanks
* Output: none
*/
void Game::setupGame(){
    //draw the top four cards to the grid
    for (int i = 0; i < 4; i++) {
        Card *initcard = mines.draw();
        grid[2][i] = initcard;
    }
    for (int i = 0; i < 4; i++) {
        Card *initcard = transport.draw();
        grid[1][i] = initcard;
    }
    for (int i = 0; i < 4; i++) {
        Card *initcard = vendors.draw();
        grid[0][i] = initcard;
    }
    //initialize the gem bank
    for (int i = 0; i < 5; i++) {
        gem_bank[i] = 4;
    }
    gem_bank[5] = 5;
     //initialize players
    player[0] = new Player();
    player[1] = new Player();
}

/* ~Game
* Input: none
* Description: Game destructor
* Output: deletes the cards in the decks and the grid, also deletes players
*/
Game::~Game(){
    //delete the grid
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 4; j++){
            delete grid[i][j];
        }
    }
    //delete leftover cards in the decks
    for(int i = 0; i < mines.getdeckSize(); i++){
        delete mines.at(i);
    }
    for(int i = 0; i < transport.getdeckSize(); i++){
        delete transport.at(i);
    }
    for(int i = 0; i < vendors.getdeckSize(); i++){
        delete vendors.at(i);
    }
    for(int i = 0; i < nobles.getdeckSize(); i++){
        delete nobles.at(i);
    }
    //delete players
    delete player[0];
    delete player[1];
}

/* playGame
* Input: none
* Description: runs player turns until one player has over 15 prestige points
* Output: printed statements, prints the board
*/
void Game::playGame(){
    bool game_over = false;
    bool player1_turn = true;
    int quit = 0;
    while (!game_over) {
        //reset the screen
        clearBoard();
        screen_clear();
        screen_home();
        //draw the board
        drawBoard();
        if(player[0]->totalPrestige() >= 15){
            cout << "PLAYER 2, enter your next move: ";
            p_and_e(&game_over, player1_turn);
            quit = 1;
            game_over = true;
        }else if (player[1]->totalPrestige() >= 15){
            quit = 1;
            game_over = true;
        }else{
            if(player1_turn){
            cout << "PLAYER 1, enter your next move: ";
            }else{
                cout << "PLAYER 2, enter your next move: ";
            }p_and_e(&game_over, player1_turn);
        }
        player1_turn = !player1_turn;
    }
    //end of game stuff
    End_Of_Game(quit);
}

/* End_Of_Game
* Input: an integer value
* Description: determines a specific printed output statement based on whether
* a player has greater prestige than another. If the prestige values are the
* same, then it compares the amount of cards each player has purchased to
* determine the outputted statement
* Output: printed statements
*/
void Game::End_Of_Game(int quit){
    if(quit != 0){
        int P1, P2;
        P1 = player[0]->totalPrestige();
        P2 = player[1]->totalPrestige();
        if(P1 > P2){
            cout << "Congratulations Player 1: YOU WIN!!!!" << endl;
        }else if(P2 > P1){
            cout << "Congratulations Player 2: YOU WIN!!!!" << endl;
        }else if(P1 == P2){
            if(player[0]->getPurchases() == player[1]->getPurchases()){
            cout << "You losers tied - BORING!!!!" << endl;
            }else if(player[0]->getPurchases() > player[1]->getPurchases()){
                cout << "Congratulations Player 2: YOU WIN!!!!" << endl;
            }else{
                cout << "Congratulations Player 1: YOU WIN!!!!" << endl;
            }
        }
    }
}

//Get the gem color associated with the given index
string Game::indexToColor(int index){
    return colors[index];
}

//draw all of the elements onto the game board
void Game::drawBoard(){
    int vpos = 0;
    int hpos = 1;

    //draw the card decks
    if (!vendors.empty()) {
        drawDeck(vpos, hpos, "Vendors");
    }
    vpos += CARD_HEIGHT + 1;
    if (!transport.empty()) {
        drawDeck(vpos, hpos, "Transport");
    }
    vpos += CARD_HEIGHT + 1;
    if (!mines.empty()) {
        drawDeck(vpos, hpos, "Mines");
    }

    //draw the in play cards
    vpos = 0;
    hpos = CARD_WIDTH + 2;
    for (int i = 0; i < CARD_ROWS; i++) {
        for (int j = 0; j < CARD_COLS; j++) {
            if (grid[i][j] != nullptr) {
                drawCard(vpos, hpos, grid[i][j]);
            }
            hpos += CARD_WIDTH + 1;
        }
        vpos += CARD_HEIGHT + 1;
        hpos = CARD_WIDTH + 2;
    }

    //draw the gems
    int gemOffset = ((CARD_WIDTH + 1) * 5) + 3;
    vpos = 1;
    hpos = gemOffset;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            int index = (i * 2) + j;
            if (gem_bank[index] > 0) {
                board[vpos][hpos + 5] = gem_bank[index] + 48;
                board_color[vpos][hpos + 5] = indexToColor(index);
                drawGem(vpos + 1, hpos, indexToColor(index));
            }
            hpos += CARD_WIDTH;
        }
        vpos += CARD_HEIGHT + 1;
        hpos = gemOffset;
    }

    //draw players
    drawPlayer(vpos + 1, 1, player[0]);
    drawPlayer(vpos + 1, ((CARD_WIDTH + 1) * 4), player[1]);

    //draw nobles
    if (play_nobles) {
        hpos = ((CARD_WIDTH + 1) * 7) + 2;
        vpos = 2;
        for (int i = 0; i < NUM_NOBLES; i++) {
            if (nobles.at(i) != nullptr) {
                drawNoble(vpos, hpos, nobles.at(i));
            }
            vpos += CARD_HEIGHT + 1;
        }
    }

    //print out the finished board
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (board_color[i][j] != "white") {
                screen_fg(board_color[i][j]);
            }
            cout << board[i][j];
            screen_fg("white");
        }
        cout << endl;
    }
    cout << endl;
}

//draws a noble at the specified position of the board
void Game::drawNoble(int vpos, int hpos, Card *c){
    string top = "|\\  /*\\  /|";
    string second = "| \\/   \\/ |";
    string blank = "N         N";
    string bottom = "~~~~~~~~~~~";

    //draw the basic card outline
    int length = top.length();
    for (int i = 0; i < length; i++) {
        board[vpos][hpos + i] = top[i];
        board[vpos + 1][hpos + i] = second[i];

        for (int j = 2; j < 5; j++) {
            board[vpos + j][hpos + i] = blank[i];
        }
        board[vpos + 5][hpos + i] = bottom[i];
    }

    //draw the prices
    vpos += 2;
    for (int i = 0; i < GEMS - 1; i++) {
        int price = c->getPrice(i);
        if (price > 0) {
            board_color[vpos][hpos + 4] = indexToColor(i);
            board_color[vpos][hpos + 5] = indexToColor(i);
            board_color[vpos][hpos + 6] = indexToColor(i);
            board[vpos][hpos + 4] = '|';
            board[vpos][hpos + 5] = price + 48;
            board[vpos][hpos + 6] = '|';
            vpos++;
        }
    }
}

//draws a player at the specified position of the board
void Game::drawPlayer(int vpos, int hpos, Player *p){
    //player string
    string prestige = to_string(p->totalPrestige());
    string player_s;
    if (hpos < 10) {
        player_s = " PLAYER 1: " + prestige + " prestige point(s)";
    } else {
        player_s = " PLAYER 2: " + prestige + " prestige point(s)";
    }
    int length = player_s.length();
    for (int i = 0; i < length; i++) {
        board[vpos][hpos + i] = player_s[i];
    }

    //bonus string
    vpos++;
    string bonus_s = "Discounts: ";
    length = bonus_s.length();
    for (int i = 0; i < GEMS - 1; i++) {
        int bonus = p->getDiscount(i);
        bonus_s += "|" + to_string(bonus) + "| ";

        board_color[vpos][hpos + length] = indexToColor(i);
        board_color[vpos][hpos + length + 1] = indexToColor(i);
        board_color[vpos][hpos + length + 2] = indexToColor(i);

        length += 4;
        if (bonus >= 10) {
            length += 1;
        }
    }
    for (int i = 0; i < length; i++) {
        board[vpos][hpos + i] = bonus_s[i];
    }

    //gem string
    vpos++;
    string gems_s = "     Gems: ";
    length = gems_s.length();
    int different_gems = GEMS;
    for (int i = 0; i < different_gems; i++) {
        int gems = p->getgemCount(i);
        gems_s += "(" + to_string(gems) + ") ";

        board_color[vpos][hpos + length] = indexToColor(i);
        board_color[vpos][hpos + length + 1] = indexToColor(i);
        board_color[vpos][hpos + length + 2] = indexToColor(i);

        length += 4;
    }
    for (int i = 0; i < length; i++) {
        board[vpos][hpos + i] = gems_s[i];
    }

    //reserve string
    vpos++;
    string reserve_s = " Reserved:";
    length = reserve_s.length();
    for (int i = 0; i < length; i++) {
        board[vpos][hpos + i] = reserve_s[i];
    }

    hpos += reserve_s.length();
    for (int i = 0; i < 3; i++) {
        Card *c = p->getReserve(i);
        if (c == nullptr) {
            drawDeck(vpos, hpos, "");
        } else {
            drawCard(vpos, hpos, c);
        }
        hpos += CARD_WIDTH + 1;
    }
}

//draws a card deck at the specified position of the board
void Game::drawDeck(int vpos, int hpos, string type){
    string top = "  _________  ";
    string second = " /         \\ ";
    string blank = "|           |";
    string bottom = " \\_________/ ";

    //draw the basic card outline
    int length = top.length();
    for (int i = 0; i < length; i++) {
        board[vpos][hpos + i] = top[i];
        board[vpos + 1][hpos + i] = second[i];
        for (int j = 2; j < CARD_HEIGHT; j++) {
            board[vpos + j][hpos + i] = blank[i];
        }
        board[vpos + CARD_HEIGHT][hpos + i] = bottom[i];
    }

    int start_pos = hpos + (blank.length() / 2) - (type.length() / 2);
    length = type.length();
    for (int i = 0; i < length; i++) {
        board[vpos + (CARD_HEIGHT / 2)][start_pos + i] = type[i];
    }
}

//draws a gem at the specified position of the board
void Game::drawGem(int vpos, int hpos, string color){
    string gem_image[6];
    gem_image[0] = "  _______  ";
    gem_image[1] = ".'_/_|_\\_'.";
    gem_image[2] = "\\`\\  |  /`/";
    gem_image[3] = " `\\  | //' ";
    gem_image[4] = "   `\\|/`   ";
    gem_image[5] = "     `     ";

    for (int i = 0; i < GEMS; i++) {
        int length = gem_image[i].length();
        for (int j = 0; j < length; j++) {
            board[vpos + i][hpos + j] = gem_image[i][j];
            board_color[vpos + i][hpos + j] = color;
        }
    }
}

//draws a card at the specified position of the board
void Game::drawCard(int vpos, int hpos, Card *c){
    string top = "  _________  ";
    string second = " /         \\ ";
    string blank = "|           |";
    string bottom = " \\_________/ ";

    //draw the basic card outline
    int length = top.length();
    for (int i = 0; i < length; i++) {
        board[vpos][hpos + i] = top[i];

        if (i == 8 || i == 9) {
            board_color[vpos + 1][hpos + i] = c->getGemColor();
        }
        board[vpos + 1][hpos + i] = second[i];

        for (int j = 2; j < CARD_HEIGHT; j++) {
            board[vpos + j][hpos + i] = blank[i];
        }
        board[vpos + CARD_HEIGHT][hpos + i] = bottom[i];
    }

    //draw the prestige number and gem
    board[vpos + 2][hpos + 3] = c->getPrestige() + 48;
    board_color[vpos + 2][hpos + 8] = c->getGemColor();
    board_color[vpos + 2][hpos + 9] = c->getGemColor();
    board[vpos + 2][hpos + 8] = '\\';
    board[vpos + 2][hpos + 9] = '/';
    board_color[vpos + 1][hpos + 8] = c->getGemColor();
    board_color[vpos + 1][hpos + 9] = c->getGemColor();
    board[vpos + 1][hpos + 8] = '_';
    board[vpos + 1][hpos + 9] = '_';

    //draw the prices
    vpos += 4;
    for (int i = 0; i < GEMS - 1; i++) {
        int price = c->getPrice(i);
        if (price > 0) {
            board_color[vpos][hpos + 2] = indexToColor(i);
            board_color[vpos][hpos + 3] = indexToColor(i);
            board_color[vpos][hpos + 4] = indexToColor(i);
            board[vpos][hpos + 2] = '(';
            board[vpos][hpos + 3] = price + 48;
            board[vpos][hpos + 4] = ')';
            vpos++;
        }
    }
}

//clear the board display
void Game::clearBoard(){
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            board[i][j] = ' ';
            board_color[i][j] = "white";
        }
    }
}

/* p_and_e
* Input: a pointer to a bool, and a bool
* Description: asks for an input command and does different outputs depending
* on the command-- basically does a valid turn for a player
* Output: none
*/
void Game::p_and_e(bool *game_over, bool player1_turn){
    //cin an input
    string command;
    cin >> command;
    int playerNum;
    //make an integer for whose turn it is for easy player array access
    if(player1_turn){
        playerNum = 0;
    }else{
        playerNum = 1;
    }
    //query loop
    if(command == "q"){
        *game_over = true;
    }else if(command == "p2"){
        takeTwoGems(game_over, player1_turn, playerNum);
    }else if(command == "p3"){
        takeThreeGems(game_over, player1_turn, playerNum);
    }else if(command == "r"){
        reserveCard(game_over, player1_turn, playerNum);
    }else if(command == "b"){
        buyCard(game_over, player1_turn, playerNum);
    }else if(command == "br"){
        buyReserveCard(game_over, player1_turn, playerNum);
    }else{
        cout << "Invalid move - enter a valid move: ";
        p_and_e(game_over, player1_turn);
    }
}

// setGemBank()
// Input: color integer and amount
// Description: add or subtract values from the gem bank
// Output: none
void Game::setGemBank(int color, int amount){
    gem_bank[color] += amount;
}

/* takeTwoGems
* Input: a pointer to a bool, a bool, and the integer for which player's turn
* it is
* Description: asks for one color, and if the gem bank has four of that color,
* adds two of that color to a player's gemCount, subtracts two from the bank
* Output: none
*/
void Game::takeTwoGems(bool *game_over, bool player1_turn, int playerNum){
    string color;
    cin >> color;
    //check if the input is a valid color
    if(colorChecker(color)){
        cout << "Invalid move (invalid color) - enter a valid move: ";
        p_and_e(game_over, player1_turn);
        cout << endl;
    }
    //check if the gembank has four gems of the specified color
    for(int i = 0; i < 5; i++){
        if(color == colors[i]){
            if(gem_bank[i] != 4){
                cout << "Invalid move (unavailable gems) - enter a ";
                cout << "valid move: ";
                p_and_e(game_over, player1_turn);
                cout << endl;
            }else if(gem_bank[i] == 4){
                setGemBank(i, -2);
                player[playerNum]->setGemCount(i, 2);
            }
        }
    }
    //check if the player has more than ten gems total in their gemCount
    tenGems(playerNum);
}

/* colorChecker
* Input: a string
* Description: Checks to see if an inputted color is a valid color for the game
* Output: true/false
*/
bool Game::colorChecker(string color){
    for(int i = 0; i < 5; i++){
        if(color == colors[i]){
            return false;
        }
    }
    return true;
}

/* gemChecker
* Input: a string
* Description: Checks to see if the gem bank is empty for an inputted color
* Output: true/false
*/
bool Game::gemChecker(string color){
    for(int i = 0; i < 5; i++){
        if(color == colors[i]){
            if (gem_bank[i] == 0){
                return true;
            }
        }
    } 
    return false;
}

/* takeThreeGems
* Input: a pointer to a bool, a bool, and the integer for which player's turn
* it is
* Description: asks for three colors, and if the gem bank is not empty for
* those three colors, which are checked to be valid, adds one of each color 
* to a player's gemCount, subtracting one from the bank per taken color
* Output: none
*/
void Game::takeThreeGems(bool *game_over, bool player1_turn, int playerNum){
    string color1, color2, color3, colorInputs[3];
    cin >> color1 >> color2 >> color3;
    if(color1 == color2 || color2 == color3 || color1 == color3){
        cout << "Invalid move (duplicate color) - enter a valid move: ";
        p_and_e(game_over, player1_turn);
        cout << endl;
    }else if(colorChecker(color1) || colorChecker(color2) || 
             colorChecker(color3)){
        cout << "Invalid move (invalid color) - enter a valid move: ";
        p_and_e(game_over, player1_turn);
        cout << endl;
    }else if(gemChecker(color1)|| gemChecker(color2) || gemChecker(color3)){
        cout << "Invalid move (unavailable gems) - enter a valid move: ";
                p_and_e(game_over, player1_turn);
                cout << endl;
    }else{
        colorInputs[0] = color1;
        colorInputs[1] = color2;
        colorInputs[2] = color3;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 5; j++){
                if(colorInputs[i] == colors[j]){
                    setGemBank(j, -1);
                    player[playerNum]->setGemCount(j, 1);
                }
            }
        }
    }
    tenGems(playerNum);
}

/* tenGems
* Input: a pointer to a bool, a bool, and the integer for which player's turn
* it is
* Description: Checks if a player's totalGems is more than ten, and if it is,
* makes them return gems until they have ten
* Output: none
*/
void Game::tenGems(int playerNum){
    int totalGems = player[playerNum]->gettotalGems();
    //while loop for over ten gems, redrawing board each time a gem is returned
    while(totalGems > 10){
        clearBoard();
        screen_clear();
        screen_home();
        drawBoard();
        string indexColor;
        cout << "PLAYER " << (playerNum + 1) <<  ", you have more than 10" <<
        " gems! Name one gem you would like to return: ";
        cin >> indexColor;
        while(colorChecker(indexColor) && indexColor != "gold"){
            cout << "Invalid color. Name one gem you would like to return: ";
            cin >> indexColor;
        }
        for(int i = 0; i < 6; i++){
            if(colors[i] == indexColor){
                if(player[playerNum]->getgemCount(i) != 0){
                    player[playerNum]->setGemCount(i, -1);
                    setGemBank(i, 1);
                }else{
                cout << "Invalid color. Name one gem you would like" <<
                " to return: ";
                cin >> indexColor;
                }
            }
        }
        totalGems -= 1;
    }
}

/* reserveCard
* Input: a pointer to a bool, a bool, and the integer for which player's turn
* it is
* Description: takes a card from the grid, passes it into the first open
* reserve spot for a player, and fills the grid with a new card from the 
* right deck, adds a gold gem to the players gem count if there is still gold
* in the bank
* Output: none
*/
void Game::reserveCard(bool *game_over, bool player1_turn, int playerNum){
    string type, column;
    cin >> type >> column;
    int index = 0;
    //row and column checks
    if(typeCheck(type)){
        cout << "Invalid move (invalid card type) - enter a valid move: ";
        p_and_e(game_over, player1_turn);
        cout << endl;
    }else if(columnCheck(column, &index)){
        cout << "Invalid move (invalid card column) - enter a valid move: ";
        p_and_e(game_over, player1_turn);
        cout << endl;
    }//check if all the reserve slots are full
    else if(fullResCheck(playerNum)){
        cout << "Invalid move (reserve is already full) - enter a valid move: ";
        p_and_e(game_over, player1_turn);
        cout << endl;
    }else{
        //update everything necessary
        SetReserve(playerNum, type, index);
        updateGrid(type, index);
        addGoldGem(playerNum);
        tenGems(playerNum);
    }
}

/* takeTwoGems
* Input: a pointer to a bool, a bool, and the integer for which player's turn
* it is
* Description: asks for one color, and if the gem bank has four of that color,
* adds two of that color to a player's gemCount, subtracts two from the bank
* Output: none
*/
void Game::updateGrid(string type, int index){
    if(type == "m"){
            Card *initcard = mines.draw();
            grid[2][index - 1] = initcard;
        }else if(type == "t"){
            Card *initcard = transport.draw();
            grid[1][index - 1] = initcard;
        }else if(type == "v"){
            Card *initcard = vendors.draw();
            grid[0][index - 1] = initcard;
        }
}

/* typeCheck
* Input: a string
* Description: Makes sure a valid type of card is inputted 
* Output: true/false
*/
bool Game::typeCheck(string type){
    if(type == "m" || type == "v" || type == "t"){
        return false;
    }
    return true;
}

/* columnCheck
* Input: a string, and a pointer to an integer
* Description: Makes sure a valid column of grid is inputted, and then updates
* an integer to a pointer because the command was read in as a string to deal
* with cases where someone inputs a string, even though a correct input would
* be an integer
* Output: true/false
*/
bool Game::columnCheck(string column, int *index){
    //update the integer pointer if the column is correct
    if(column == "1"){
        *index = 1;
    }
    if(column == "2"){
        *index = 2;
    }
    if(column == "3"){
        *index = 3;
    }
    if(column == "4"){
        *index = 4;
    }
    //true/false checks for column input correctness
    if(column == "1" || column == "2" || column == "3" || column == "4"){
        return false;
    }
    return true;
    
}

/* fullresCheck
* Input: an integer
* Description: Checks if a player's reserve is full or not
* Output: true/false
*/
bool Game::fullResCheck(int playerNum){
    for(int i = 0; i < 3; i++){
        if(player[playerNum]->getReserve(i) == nullptr){
            return false;
        }
    }
    return true;
}

/* Card *findGridCard
* Input: a string and an integer
* Description: goes to the spot in the grid from the specified inputs and
* returns the card pointer at that location 
* Output: a card pointer
*/
Card *Game::findGridCard(string type, int index){
    //make new card pointer
    Card *findCard = nullptr;
    //go to right spot in grid
    if(type == "m"){
        findCard = grid[2][index - 1];
    }else if(type == "t"){
        findCard = grid[1][index - 1];
    }else if(type == "v"){
        findCard = grid[0][index - 1];
    }
    return findCard;
}

/* SetReserve
* Input: two integers and a string
* Description: Sets the reserve of a player at the next empty location to 
* a card pointer from the grid using specified inputs
* Output: none
*/
void Game::SetReserve(int playerNum, string type, int index){
    if(player[playerNum]->getReserve(0) == nullptr){
        player[playerNum]->setReserve(0, findGridCard(type, index));
    }else if(player[playerNum]->getReserve(1) == nullptr){
        player[playerNum]->setReserve(1, findGridCard(type, index));
    }else if(player[playerNum]->getReserve(2) == nullptr){
        player[playerNum]->setReserve(2, findGridCard(type, index));
    }
    resetGrid(type, index);
}

/* addGoldGem
* Input: an integer
* Description: (when reserve called) adds a gold gem to a player's gemCount
* and subtracts one from the bank
* Output: none
*/
void Game::addGoldGem(int playerNum){
    if(gem_bank[5] != 0){
        player[playerNum]->setGemCount(5, 1);
        setGemBank(5, -1);
    }
}

/* buyCard
* Input: a pointer to a bool, a bool, and the integer for which player's turn
* it is
* Description: ensures a buy is valid, and if it is, buys the card from the
* grid and updates all the necessary indices
* Output: none
*/
void Game::buyCard(bool *game_over, bool player1_turn, int playerNum){
    string type, column;
    cin >> type >> column;
    int index = 0;
    //check rows and column
    if(typeCheck(type)){
        cout << "Invalid move (invalid card type) - enter a valid move: ";
        p_and_e(game_over, player1_turn);
        cout << endl;
    }else if(columnCheck(column, &index)){
        cout << "Invalid move (invalid card column) - enter a valid move: ";
        p_and_e(game_over, player1_turn);
        cout << endl;
    }//checks if purchase checks out
    else if(validPurchase(type, index, playerNum)){
        cout << "Invalid move (cannot afford card) - enter a valid move: ";
        p_and_e(game_over, player1_turn);
        cout << endl;
    }else{
        //update all the necessary results of a card being bought
        updateDiscounts(type, index, playerNum);
        updatePrestige(type, index, playerNum);
        resetGrid(type, index);
        updateGrid(type, index);
        player[playerNum]->setPurchases();
    }
}

/* validPurchase
* Input: a string, two integers
* Description: takes a card from the grid, and checks if a player can validly
* buy it with his gems, discounts, and gold-- updates extra things for external
* functionality if the purchase can be done
* Output: true/false
*/
bool Game::validPurchase(string type, int index, int playerNum){
    Card *boughtCard = findGridCard(type, index);
    int cardPrice[5], PGems[5], dGems[5], neededGold[5], usedGems[5];
    int goldGems = player[playerNum]->getgemCount(5);
    int spentGold = 0;
    //large for loop to make update the necessary arrays for later functionality
    for(int i = 0; i < 5; i++){
        cardPrice[i] = boughtCard->getPrice(i);
        PGems[i] = player[playerNum]->getgemCount(i);
        dGems[i] = player[playerNum]->getDiscount(i);
        usedGems[i] = cardPrice[i] - dGems[i];
        neededGold[i] = needGold(playerNum, i, &goldGems, boughtCard, usedGems,
        &spentGold);
        if(usedGems[i] < 0){
            usedGems[i] = 0;
        }
    }
    for(int i = 0; i < 5; i++){
        if(cardPrice[i] > (PGems[i] + dGems[i] + neededGold[i])){
            return true;
        }
    }
    //update gembank, gemcount, gold, according to how a card is bought
    for(int i = 0; i < 5; i++){
            player[playerNum]->setGemCount(i, -usedGems[i]);
            setGemBank(i, usedGems[i]);
    }
    setGemBank(5, spentGold);
    player[playerNum]->setGemCount(5, -spentGold);
    return false;
}

/* needGold
* Input: two integers, an integer pointer, and a card pointer
* Description: checks if a player needs to use gold to buy a card color by color
* Output: an integer
*/
int Game::needGold(int playerNum, int j, int *goldGems, Card *Card, 
                   int usedGems[], int *spentGold){
    int Gcount = 0;
    while(*goldGems != 0){
        if(Card->getPrice(j) > player[playerNum]->getgemCount(j) + 
        player[playerNum]->getDiscount(j) + Gcount){
            //update all the necessary parts for functionality
            usedGems[j] -= 1;
            Gcount++;
            *spentGold =+1;
            *goldGems -= 1;
        }else{
            //needed because the function would run 
            return Gcount;
        }
    }
    return Gcount;
}

/* resetGrid
* Input: a string and an integer
* Description: resets the grid to nullptr according to the inputted information
* Output: none
*/
void Game::resetGrid(string type, int index){
    if(type == "m"){
        grid[2][index - 1] = nullptr;
    }else if(type == "t"){
        grid[1][index - 1] = nullptr;
    }else if(type == "v"){
        grid[0][index - 1] = nullptr;
    }
}

/* updateDiscounts
* Input: a string and two integers
* Description: updates the discount of a player according to the card they buy
* Output: none
*/
void Game::updateDiscounts(string type, int index, int playerNum){
    //if else here needed so it works with reserve buy and regular buy
    if(type != "reserve"){
        Card *boughtCard = findGridCard(type, index);
        string discountColor = boughtCard->getGemColor();
        for(int i = 0; i < 5; i++){
            if(discountColor == colors[i]){
                player[playerNum]->setDiscount(i);
            }
        }
    }else{
        Card *boughtCard = player[playerNum]->getReserve(index);
        string discountColor = boughtCard->getGemColor();
        for(int i = 0; i < 5; i++){
            if(discountColor == colors[i]){
                player[playerNum]->setDiscount(i);
            }
        }
    }
}

/* updateDiscounts
* Input: a string and two integers
* Description: updates the prestige of a player according to the card they buy,
* then deletes the card because that will be the last time it is used
* Output: none
*/
void Game::updatePrestige(string type, int index, int playerNum){
    //if else loop necessary to work with buy and buy Reserve, deletes after
    if(type != "reserve"){
        Card *boughtCard = findGridCard(type, index);
        int prestigePts = boughtCard->getPrestige();
        player[playerNum]->setPrestige(prestigePts);
        delete boughtCard;
    }else{
        Card *boughtCard = player[playerNum]->getReserve(index);
        int prestigePts = boughtCard->getPrestige();
        player[playerNum]->setPrestige(prestigePts);
        delete boughtCard;
    }
}

/* buyReserveCard
* Input: a pointer to a bool, a bool, and the integer for which player's turn
* it is
* Description: ensures a buy is valid, and if it is, buys the card from a
* player's reserve and updates all the necessary indices
* Output: none
*/
void Game::buyReserveCard(bool *game_over, bool player1_turn, int playerNum){
    string column;
    cin >> column;
    int index = 0;
    //check if the reserve at the inputted index has a card
    if(reserveCheck(column, &index) || (player[playerNum]->getReserve(index) 
       == nullptr)){
        cout << "Invalid move (no card at that index) - enter a valid move: ";
            p_and_e(game_over, player1_turn);
            cout << endl;
    }//check if the card can be bought using the player's gems and discounts
    else if(validRPurchase(index, playerNum)){
        cout << "Invalid move (cannot afford card) - enter a valid move: ";
        p_and_e(game_over, player1_turn);
        cout << endl;
    }else{
        //update the needed info based on the bought card's info, make a string
        //to pass into these functions so the functions can be used in both
        //buy and buy reserve
        string type = "reserve";
        updateDiscounts(type, index, playerNum);
        updatePrestige(type, index, playerNum);
        Card *blankCard = nullptr;
        player[playerNum]->setReserve(index, blankCard);
        player[playerNum]->setPurchases();
    }
}

/* reserveCheck
* Input: a string and a integer pointer
* Description: Makes sure a valid column of grid is inputted, and then updates
* an integer to a pointer because the command was read in as a string to deal
* with cases where someone inputs a string, even though a correct input would
* be an integer
* Output: true/false
*/
bool Game::reserveCheck(string column, int *index){
    //update integer pointer
    if(column == "1"){
        *index = 0;
    }
    if(column == "2"){
        *index = 1;
    }
    if(column == "3"){
        *index = 2;
    }
    //true false check
    if(column == "1" || column == "2" || column == "3"){
        return false;
    }
    return true;
}

/* validRPurchase
* Input: two integers
* Description: takes a card from the reserve, and checks if a player can validly
* buy it with gems, discounts, and gold-- updates extra things for external
* functionality if the purchase can be done
* Output: true/false
*/
bool Game::validRPurchase(int index, int playerNum){
    Card *boughtCard = player[playerNum]->getReserve(index);
    int cardPrice[5], PGems[5], dGems[5], neededGold[5], usedGems[5];
    int goldGems = player[playerNum]->getgemCount(5);
    int spentGold = 0;
    //large for loop to update all the important arrays to be used
    for(int i = 0; i < 5; i++){
        cardPrice[i] = boughtCard->getPrice(i);
        PGems[i] = player[playerNum]->getgemCount(i);
        dGems[i] = player[playerNum]->getDiscount(i);
        usedGems[i] = cardPrice[i] - dGems[i];
        neededGold[i] = needGold(playerNum, i, &goldGems, boughtCard, usedGems,
        &spentGold);
        if(usedGems[i] < 0){
            usedGems[i] = 0;
        }
    }
    for(int i = 0; i < 5; i++){
        if(cardPrice[i] > (PGems[i] + dGems[i] + neededGold[i])){
            return true;
        }
    }
    //functionality updates
    for(int i = 0; i < 5; i++){
        player[playerNum]->setGemCount(i, -usedGems[i]);
        setGemBank(i, usedGems[i]);
    }
    setGemBank(5, spentGold);
    player[playerNum]->setGemCount(5, -spentGold);
    return false;
}