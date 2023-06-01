/*
 * snowcrash.cpp
 * Purpose: Unscramble a 10x10 bitmap in four phases to determine what English
 *          letter it encodes.
 * Author: Luke Randolph (lrando01)
 * Partner: Charlie Mclean for lab Parts 2/3
 * Date Started: February 9, 2023
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
    unscramble_ph4(letter);
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

void unscramble_ph4(int letter[SIZE][SIZE])
{
    cout << "Unscrambling Phase 4\n";

    int start;
    /* Undo single place array changes from phase 4 */
    start = letter[4][7];
    letter[4][7] = letter[6][5];
    letter[6][5] = letter[4][2];
    letter[4][2] = letter[3][5];
    letter[3][5] = start;

    start = letter[6][7];
    letter[6][7] = letter[6][2];
    letter[6][2] = letter[3][5];
    letter[3][5] = start;

    start = letter[4][5];
    letter[4][5] = letter[4][4];
    letter[4][4] = start;
}

void unscramble_ph3(int letter[SIZE][SIZE])
{
    cout << "Unscrambling Phase 3\n";
    /* Make a temporary array */
    int temp[SIZE][SIZE];

    /* Make the temporary array a 90 degree shift of letter */
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            temp[SIZE - j - 1][i] = letter[i][j];
        }        
    }

    /* Set the temporary array into the actual array */
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            letter[i][j] = temp[i][j];
        }        
    }
}

void unscramble_ph2(int letter[SIZE][SIZE])
{
    cout << "Unscrambling Phase 2\n";

    /* Make a new 10x10 array */
    int quadrant[SIZE][SIZE];
    
    for(int i = 0; i < SIZE/2; i++)
    {
        for(int j = 0; j < SIZE/2; j++)
        {
            /* Set Q1 of the new array to be Q2 of letter array */
            quadrant[i][j] = letter[i][j + 5];
            /* Set Q2 of the new array to be Q4 of letter array */
            quadrant[i][j + 5] = letter[i + 5][j + 5];
            /* Set Q3 of the new awway to be Q3 of letter array */
            quadrant[i + 5][j] = letter[i + 5][j];
            /* Set Q4 of the new array to be Q1 of letter array*/
            quadrant[i + 5][j + 5] = letter[i][j];
        }        
    }
    /* Set letter array to be the array we just set */
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            letter[i][j] = quadrant[i][j];
        }        
    }
}

void unscramble_ph1(int letter[SIZE][SIZE])
{
    cout << "Unscrambling Phase 1\n";
    /* Undo the shift by 1 for the i+j=even parts of the array*/
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            if((i + j) % 2 == 0)
            {
                letter[i][j] = (letter[i][j] + 1) % 2;
            }
        }
    }
    /* Undo the 1-down in column shift for all array positions */
    int temp[SIZE];
    int offset = 19;

    for(int j = 0; j < SIZE; j++)
    {
        for(int i = 0; i < SIZE; i++)
        {
            temp[(offset + i) % SIZE] = letter[i][j];  
        }        

        for(int i = 0; i < SIZE; i++)
        {
            letter[i][j] = temp[i];  
        }        

        offset -= 2;
    }
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
            /* Set the 10x10 array "letter" from the characters */
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
