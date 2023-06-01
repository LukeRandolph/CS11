/*
 * tradecraft.cpp
 * purpose: To determine the shift value of a Caesar cipher encrypted file
 * author: Luke Randolph
 * Date Started: February 17, 2023
 */

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

char ReadFile(string filename);
int FindShiftAmt(char c, string filename);
string FindOneCharString(string filename);

int main(int argc, char *argv[])
{
    //make sure a file is given in command line
    if (argc < 2) {
        cerr << "ERROR: A filename must be specified as the first argument.\n";
        exit(EXIT_FAILURE);
    }
    //declares a value, assigning it to be most used char in the file
    char most_frequent = ReadFile(argv[1]);
    //receives shift amount
    int shift = FindShiftAmt(most_frequent, argv[1]);
    //print shift amount out
    cout << "The shift amount is: " << shift << endl;
    return 0;
}

  /* ReadFile()
   * Input: String of file it wants to open
   * Description: opens the file and returns the most used
   *              character
   * Output: Prints error message if not able to open file
   */
char ReadFile(string filename) {
    //open file and check for errors
    ifstream infile;
    infile.open(filename);
    if (infile.fail()) {
        cerr << "ERROR: Could not open file." << endl;
        exit(EXIT_FAILURE);
    }
    //declares letter array and count array
    char letter[26], infile_char;
    int lettercount[26];
    int ascii = 97;
    //initializes both letter array and count array
    for (int i=0; i<26; i++) {
        letter[i] = (char)(ascii);
        lettercount[i] = 0;
        ascii++;
    }
    //gets the counts of every letter of alphabet
    while (infile.get(infile_char)) {
        char temp_char = tolower(infile_char);
        for (int i=0; i<26; i++) {
            if (letter[i] == temp_char) {
                lettercount[i]++;
            }
        }
    }
    //fills array of counts for each letter of alphabet
    int count = 0;
    for (int i=0; i<26; i++) {
        if (lettercount[i] > count) {
            infile_char = letter[i];
            count = lettercount[i];
        }
    }
    return infile_char;
}

 /* FindShiftAmt()
   * Input: Most used char, string of file it wants to open
   * Description: finds shift amt from the char to 'e' or 't'
   * Output: Nothing
   */
int FindShiftAmt(char c, string filename) {
    //finds shift value from 'e'
    int shiftamt = (int)(c) - 101;
    if (shiftamt < 0) {
        shiftamt += 26;
    } 
    //checks if shift value from 'e' shifts one letter words from file to 'a' or 'i'
    string one_char = FindOneCharString(filename);
    char test_char = tolower(one_char[0]);
    int test_ascii = (int)(test_char) - shiftamt;
    if (test_ascii < 97) {
        test_ascii += 26;
    }
    //if it doesn't, find shift value from 't'
    if ((char)(test_ascii) != 'a' && (char)(test_ascii) != 'i') {
        shiftamt = (int)(c) - 116;
        if (shiftamt < 0) {
        shiftamt += 26;
        }
    }
    return shiftamt;
}

 /* FindOneCharString()
   * Input: String of file it wants to open
   * Description: opens the file and returns the first one
   *              letter word it finds
   * Output: Prints error message if not able to open file
   */
string FindOneCharString(string filename) {
    //open file
    ifstream infile;
    infile.open(filename);
     //check if file works
    if (infile.fail()) {
        cerr << "ERROR: Could not open file." << endl;
        exit(EXIT_FAILURE);
    }
    //declare word variable
    string word;
    //run through file to find a word of length 1
    while (!infile.eof()) {
        infile >> word;
        if (word.length() == 1) {
            break;
       }
    }
    return word;
}