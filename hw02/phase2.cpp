/*
 * Phase 2 Scrambler
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
void scramble(int letter[SIZE][SIZE]);

/*
 * The main function takes two arguments from the command line:
 * 1.) The input file to read the letter from
 * 2.) The name of the output file to write the unscrambled letter to
 */
int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        cerr << "ERROR: Not enough arguments specified\n";
        exit(EXIT_FAILURE);
    } 

    /* 2D array that will store the letter bitmap */
    int letter[SIZE][SIZE];

    /* Read the letter file into a 2D array */
    read_letter(argv[1], letter);

    /* Scramble the letter */
    scramble(letter);

    /* Write the unscrambled letter to file */
    write_letter(argv[2], letter);

    return 0;
}

/* - - - - - - - - - - - - - - - - - - - - */
/* - - - - - - SCRAMBLING CODE - - - - - - */
/* - - - - - - - - - - - - - - - - - - - - */
void scramble(int letter[SIZE][SIZE])
{

     /* For this phase, each 10x10 letter has been broken into four, 
     * 5x5 quadrants:
     *
     * |---------|---------|
     * |         |         |
     * |    1    |    2    |
     * |         |         |
     * |---------|---------|
     * |         |         |
     * |    3    |    4    |
     * |         |         |
     * |---------|---------|
     *
     * These quadrants have been scrambled into the following new arrangement:
     *
     * |---------|---------|
     * |         |         |
     * |    4    |    1    |
     * |         |         |
     * |---------|---------|
     * |         |         |
     * |    3    |    2    |
     * |         |         |
     * |---------|---------|
     *
     * Note that the data WITHIN each quadrant has not been scrambled in any 
     * way. For example, quadrant 2 from the original 2D array is identical to 
     * quadrant 2 in the scrambled array (it has just moved to a different
     * location).
     *
     * Your task is to reverse this scrambling.
     */
    
}

/*
 * Reads a letter from the specified file into a 2D array of ints
 * Input: the file name and the 2D array to write into
 */
void read_letter(string filename, int letter[SIZE][SIZE])
{
    /* Declare a variable to read in from the file */
    ifstream infile;
    infile.open(filename.c_str()); /* C-style string required */

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
            /* Convert the char to an int and store it in out letter array */
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
    outfile.open(filename.c_str()); // C-style string required

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
