/*
 * top3.cpp
 * Purpose: List the three greatest numbers in order out of a list.
 * Author: Luke Randolph (lrando01)
 * Date Started: February 19, 2023
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cerr << "ERROR: A filename must be specified as the first argument.\n";
        exit(EXIT_FAILURE);
    }
    //open file
    ifstream infile;
    infile.open(argv[1]);
    //check if file works
    if (infile.fail()) {
        cerr << "ERROR: Could not open file." << endl;
        exit(EXIT_FAILURE);
    }
    //make 3 variables to hold 3 greatest numbers
    int top1 = 0;
    int top2 = 0;
    int top3 = 0;
    //make holder variables
    int next_int, temp_int;
    //run eof
    while (!infile.eof()){
        infile >> next_int;
        //check character by character of the file for greatest number
        if (next_int >= top1) {
            temp_int = next_int;
            next_int = top1;
            top1 = temp_int;
        } 
        //set top2 to be old top1
        if (next_int >= top2) {
            temp_int = next_int;
            next_int = top2;
            top2 = temp_int;
        }
        //set top3 to be old top2
        if (next_int >= top3) {
            temp_int = next_int;
            next_int = top3;
            top3 = temp_int;
        }
    }
    infile.close();
    //read out 3 greatest numbers
    cout << top1 << endl;
    cout << top2 << endl;
    cout << top3 << endl;

    return 0;
}


