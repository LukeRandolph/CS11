/*
 * snowcrash.cpp
 * Purpose: Unscramble a 10x10 bitmap in four phases to determine what English
 *          letter it encodes.
 * Author: {YOUR NAME AND CS LOGIN}
 */

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

const int SIZE = 10;

/* Function declarations must come before they are called */
void read_letter(string filename, int letter[SIZE][SIZE]);
void write_letter(string filename, int letter[SIZE][SIZE]);
void unscramble_ph4(int letter[SIZE][SIZE]);
void unscramble_ph3(int letter[SIZE][SIZE]);
void unscramble_ph2(int letter[SIZE][SIZE]);
void unscramble_ph1(int letter[SIZE][SIZE]); 

/*
 * The main function takes three arguments from the terminal:
 * 1.) The phase to unscramble down to
 * 2.) The input file to read the letter from
 * 3.) The name of the output file to write the unscrambled letter to
 */
int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        cerr << "ERROR: Not enough arguments specified\n";
        exit(EXIT_FAILURE);
    } 
    
    /* 2D array that will store the letter bitmap */
    int letter[SIZE][SIZE];
    int phase = (int)(argv[1][0]  - '0');
    
    /* Read the letter file into a 2D array */
    read_letter(argv[2], letter);
    
    /* Unscramble the letter */
    int result = unscramble_ph4(int letter[SIZE][SIZE], 9);
    if (phase <= 3) unscramble_ph3(letter); 
    if (phase <= 2) unscramble_ph2(letter);
    if (phase <= 1) unscramble_ph1(letter);
    
    /* Write the unscrambled letter to file */
    write_letter(argv[3], letter);
    
    return 0;
}

/* - - - - - - - - - - - - - - - - - - - - - */
/* - - - - - YOUR CODE GOES BELOW  - - - - - */
/* - - - - - - - - - - - - - - - - - - - - - */

void unscramble_ph4(letter[SIZE][SIZE])
{
    cout << "Unscrambling Phase 4\n";

    int start;


    start = letter[4][7];
    letter[4][7] = letter[6][5];
    letter[6][5] = letter[4][2];
    letter[4][2] = letter[3][5];
    letter[3][5] = start;

    return "I did it!";
}

void unscramble_ph3(int letter[SIZE][SIZE])
{
    cout << "Unscrambling Phase 3\n";
}

void unscramble_ph2(int letter[SIZE][SIZE])
{
    cout << "Unscrambling Phase 2\n";
}

void unscramble_ph1(int letter[SIZE][SIZE])
{
    cout << "Unscrambling Phase 1\n";
}

/* - - - - - - - - - - - - - - - - - - - - - */
/* - - - - - YOUR CODE GOES ABOVE  - - - - - */
/* - - - - - - - - - - - - - - - - - - - - - */

/*
 * Reads a letter from the specified file into a 2D array of ints
 * Input: the file name and the 2D array to write into
 */
void read_letter(string filename, int letter[SIZE][SIZE])
{
    /* Declare a variable to read in from the file */
    ifstream infile;
    infile.open(filename); 

    /* Error check */
    if (!infile.is_open())
    {
        cerr << "ERROR: Error opening file - ";
        cerr << "please check that you specified the correct file name\n";
        exit(EXIT_FAILURE);
    }

    char next_char;
    int count = 0;

    /* Read characters until we have the full 10x10 letter */
    while(count < 100)
    {
        /*
         * If we hit the end of the file before we have the full letter, 
         * we have a problem
         */
        if(infile.eof())
        {
            cerr << "ERROR: Letter file is not properly formatted.\n";
            exit(EXIT_FAILURE);
        }
        
        /* Get the next character from the file */
        infile >> next_char;
        
        if((next_char == '0') || (next_char == '1'))
        {
            /* What is the next line of code doing? */
            letter[count / SIZE][count % SIZE] = (int)(next_char - '0');
            count++;
        }
    }
    
    /* Close the file we're reading */
    infile.close();
}

/*
 * Writes a letter from a 2D array of ints into the specified file
 * Input: the file name and the 2D array to read from
 */
void write_letter(string filename, int letter[SIZE][SIZE])
{
    /* Declare a file variable to write to */
    ofstream outfile;
    outfile.open(filename); 

    /* Loop through our letter array and write out each digit */
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            outfile << letter[i][j];
        }
        outfile << endl;
    }
    
    /* Close the file we're writing to */
    outfile.close();
}
