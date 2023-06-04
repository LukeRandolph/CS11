#include <iostream>
#include <string>

using namespace std;

//Function declarations
void makeBoard(string *board);
void End_Of_Game(int quit, string *board, bool player1_turn);
void p_and_e(bool *game_over, bool player1_turn, string *board);
void drawBoard(string *board);
bool rowCheck(string rows, int *row);
bool columnCheck(string column, int *col);
bool openCheck(int row, int col, string *board);
void placeMark(bool player1_turn, string *board, int row, int col);
bool winCondition(string *board);
bool tieCheck(string *board);
bool rowWin(string *board);
bool colWin(string *board);
bool diagWin(string *board);

int main(){
    string board[16];
    makeBoard(board);
    bool game_over = false;
    bool player1_turn = true;
    int quit = 0;
    while (!game_over){
        drawBoard(board);
        if(winCondition(board) || tieCheck(board)){
            quit = 1;
            game_over = true;
        }else{
            if(player1_turn){
            cout << "PLAYER 1, enter your next move: ";
            }else{
                cout << "PLAYER 2, enter your next move: ";
            }p_and_e(&game_over, player1_turn, board);
        }
        player1_turn = !player1_turn;
    }
    End_Of_Game(quit, board, player1_turn);
    return 0;
}

void makeBoard(string *board){
    for(int i = 0; i < 16; i++){
        board[i] = " ";
    }
}

void End_Of_Game(int quit, string *board, bool player1_turn){
    if(quit != 0){
        if(!tieCheck(board)){
            if (!player1_turn){
                cout << "Congratulations Player 2: YOU WIN!!!!" << endl;
            }else{
                cout << "Congratulations Player 1: YOU WIN!!!!" << endl;
            }
        }else{
            cout << "You losers tied - BORING!!!!" << endl;
        }
    }
}

void p_and_e(bool *game_over, bool player1_turn, string *board){
    string rows, column;
    cin >> rows;
    int row, col;
    if(rows == "q"){
        *game_over = true;
    }else{
        cin >> column;
        if(rowCheck(rows, &row)){
            cout << "Invalid move (invalid row) - enter a valid move: ";
            p_and_e(game_over, player1_turn, board);
        }else if(columnCheck(column, &col)){
        cout << "Invalid move (invalid column) - enter a valid move: ";
            p_and_e(game_over, player1_turn, board);
        }else if(openCheck(row, col, board)){
            cout << "Invalid move (spot already full) - enter a valid move: ";
            p_and_e(game_over, player1_turn, board);
        }else{
            placeMark(player1_turn, board, row, col);
        }
    }
}

void drawBoard(string *board){
    cout << " 1   2   3   4  " << endl;
    cout << " " << board[0] << " | " << board[4] << " | " << board[8]
    << " | " << board[12] << "  1 " << endl;
    cout << "---------------" << endl;
    cout << " " << board[1] << " | " << board[5] << " | " << board[9]
    << " | " << board[13] << "  2 " << endl;
    cout << "---------------" << endl;
    cout << " " << board[2] << " | " << board[6] << " | " << board[10]
    << " | " << board[14] << "  3 " << endl;
    cout << "---------------" << endl;
    cout << " " << board[3] << " | " << board[7] << " | " << board[11]
    << " | " << board[15] << "  4 " << endl;
}

bool rowCheck(string rows, int *row){
    //update the integer pointer if the row is correct
    if(rows == "1"){
        *row = 0;
    }
    if(rows == "2"){
        *row = 1;
    }
    if(rows == "3"){
        *row = 2;
    }
    if(rows == "4"){
        *row = 3;
    }
    //true/false checks for row input correctness
    if(rows == "1" || rows == "2" || rows == "3" || rows == "4"){
        return false;
    }
    return true;
}

bool columnCheck(string column, int *col){
    //update the integer pointer if the column is correct
    if(column == "1"){
        *col = 0;
    }
    if(column == "2"){
        *col = 1;
    }
    if(column == "3"){
        *col = 2;
    }
    if(column == "4"){
        *col = 3;
    }
    //true/false checks for column input correctness
    if(column == "1" || column == "2" || column == "3" || column == "4"){
        return false;
    }
    return true;
}

bool openCheck(int row, int col, string *board){
    int num = ((row * 4) + col);
    if(board[num] != " "){
        return true;
    }
    return false;
}

void placeMark(bool player1_turn, string *board, int row, int col){
    int num = ((row * 4) + col);
    if(player1_turn){
        board[num] = "X";
    }else{
        board[num] = "O";
    }
}

bool winCondition(string *board){
    if (rowWin(board) || colWin(board) || diagWin(board)){
        return true;
    }
    return false;
}


bool tieCheck(string *board){
    if(!winCondition(board)){
        for(int i = 0; i < 16; i++){
            if (board[i] == " "){
                return false;
            }
        }
        return true;
    }
    return false;
}

bool colWin(string *board){
    if((board[0] != " ") && board[0] == board[1] && board[1] == board[2] &&
    board[2] == board[3]){
        return true;
    }
    if((board[4] != " ") && board[4] == board[5] && board[5] == board[6] &&
    board[6] == board[7]){
        return true;
    }
    if((board[8] != " ") && board[8] == board[9] && board[9] == board[10] &&
    board[10] == board[11]){
        return true;
    }
    if((board[12] != " ") && board[12] == board[13] && board[13] == board[14] &&
    board[14] == board[15]){
        return true;
    }
    return false;
}

bool rowWin(string *board){
    if((board[0] != " ") && board[0] == board[4] && board[4] == board[8] &&
    board[8] == board[12]){
        return true;
    }
    if((board[1] != " ") && board[1] == board[5] && board[5] == board[9] &&
    board[9] == board[13]){
        return true;
    }
    if((board[2] != " ") && board[2] == board[6] && board[6] == board[10] &&
    board[10] == board[14]){
        return true;
    }
    if((board[3] != " ") && board[3] == board[7] && board[7] == board[11] &&
    board[11] == board[15]){
        return true;
    }
    return false;
}

bool diagWin(string *board){
    if((board[0] != " ") && board[0] == board[5] && board[5] == board[10] &&
    board[10] == board[15]){
        return true;
    }
    if((board[3] != " ") && board[3] == board[6] && board[6] == board[9] &&
    board[9] == board[12]){
        return true;
    }
    return false;
}

