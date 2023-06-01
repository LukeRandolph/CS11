/*
 * cstrings.cpp
 * purpose: To determine how many substrings there are out of 
 * words in the same line of a text file
 * author: Luke Randolph
 * Date Started: February 23, 2023
 */

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cctype> //Lets us use the isalpha function

using namespace std;

const int SIZE = 50;
int read_line(ifstream &infile, char words[SIZE][SIZE]);
bool is_equal(char *word1, char *word2);
bool is_prefix(char *word1, char *word2);
char *find_substring(char *haystack, char *needle);

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cerr << "ERROR: A filename must be specified as the first argument.\n";
        exit(EXIT_FAILURE);
    }
    /* Open the file */
    ifstream infile;
    infile.open(argv[1]);
    /* Error check */
    if (infile.fail()) {
        cerr << "ERROR: Error opening file - ";
        cerr << "please check that you specified the correct file name\n";
        exit(EXIT_FAILURE);
    }
    int total_words = 0;
    char words[SIZE][SIZE];
    total_words = read_line(infile, words); //Read the first line from the file
    while (!infile.eof()) {
        /* DO NOT MODIFY THE CODE IN main() ABOVE OR BELOW THIS COMMENT BLOCK */
        for(int i = 0; i < total_words; i++){
            for(int j = 0; j < total_words; j++){
                if (find_substring(words[i], words[j]) != nullptr){
                    cout << words[j] << " is a substring of " << words[i] << endl;
                }
            }
        }
        /* DO NOT MODIFY THE CODE IN main() ABOVE OR BELOW THIS COMMENT BLOCK */
        //Read the next line from the file
	total_words = read_line(infile, words);
    }
    /* Close the file */
    infile.close();

    return 0;
}

/* is_equal
 * Arguments: two pointers to C-style strings
 * Description: determines if two C-style strings are equivalent
 * Return value: true if strings are equivalent, false otherwise
 */
bool is_equal(char *word1, char *word2)
{
    char next_char1 = 'a';
    char next_char2 = 'a';
    int length1 = 0;
    int length2 = 0;
    //find length word 1
    while (next_char1 != '\0') {
        next_char1 = word1[length1];
        length1++;
    }
    //find length word 2
    while (next_char2 != '\0') {
        next_char2 = word2[length2];
        length2++;
    }
    //check if lengths are equal
    if (length1 != length2){
        return false;
    }
    //if they are equal in length, check if letters are the same
    if (length1 == length2){
        for (int i = 0; i < length1; i++){
            if (word1[i] != word2[i]){
                return false;
            }
        }
    }
    return true;
}

/* is_prefix
 * Arguments: two pointers to C-style strings
 * Description: determines if string word2 is a prefix of string word1
 * Return value: true if word2 is a prefix of word1, false otherwise
 */
bool is_prefix(char *word1, char *word2)
{
    char next_char1= 'a';
    char next_char2 = 'a';
    int length1 = 0;
    int length2 = 0;
    //find word 1 length
    while (next_char1 != '\0') {
        next_char1 = word1[length1];
        length1++;
    }
    //find word 2 length
    while (next_char2 != '\0') {
        next_char2 = word2[length2];
        length2++;
    }
    //check if they are equal in length
    if (length1 == length2){
        return false;
    }
    //if not equal, check if the letters of the words match
    for (int i = 0; i < (length1 - 1) && i < (length2 - 1); i++){
        if (word1[i] != word2[i]){
                return false;
        } 
    }
    return true;
}

/* find_substring
 * Arguments: two pointers to C-style strings
 * Description: determines whether string 'needle' is a proper substring of
 *              string 'haystack'.
 * Return value: if 'needle' isn't a proper substring of 'haystack', return
 *               nullptr. Otherwise, return a pointer to the beginning of the
 *               first occurrence of 'needle' within 'haystack'.
 */
char *find_substring(char *haystack, char *needle)
{
   int haylength = 0;
   int needlength = 0;
   char *ptr;
   int shift = 0;
   //length of haystack
   for (int i = 0; haystack[i] != '\0'; i++){
        haylength++;
   }
   //length of needle
   for (int i = 0; needle[i] != '\0'; i++){
        needlength++;
   }
   //if haystack and needle are the same, return nullptr
   if (is_equal(haystack, needle)){
        return nullptr;
   }
   //while loop to check if needle is in haystack
   //shifting start one character over in haystack each time
   while((haylength - shift) >= needlength){
        char str[haylength];
        for (int i = shift; i < haylength; i++){
            str[i - shift] = haystack[i];
        }
        if(is_prefix(str, needle)){
            ptr = &haystack[shift];
            return ptr;
        }
        shift ++;
    }
    return nullptr;
}

/* Retrieve a line of input from a file, parse it into individual words, and
 * store those words in the "words_in_sentence" 2D-array. Each "row" of
 * words_in_sentence is another word. Return the total number of words read in.
 *
 * For example, if we read in the sentence "Here I am!", then the
 * first 3 rows (R) and first 5 columns (C) of the words_in_sentence array
 * will look like the picture belwo (the empty cells hold garbage values):
 *
 *        C0   C1   C2   C3   C4
 * R0:  | H  | e  | r  | e  | \0 |
 * R1:  | I  | \0 |    |    |    |
 * R2:  | a  | m  | \0 |    |    |
 *
 * NOTE: We have to write "ifstream &infile" as a parameter to pass an input
 * file stream correctly to a function (without needing even more pointers). If
 * you need to write a function that takes a file stream as an argument, always
 * put the '&' in front of the name of your file stream parameter.
 */
int read_line(ifstream &infile, char words_in_sentence[SIZE][SIZE])
{
    int spot = 0;
    int word_index = 0;
    char *next_word;
    char next_char;

    infile.get(next_char);
    while (!infile.eof() && next_char != '\n') {
        next_word = words_in_sentence[word_index];
        //Written question 1 asks about this loop
        while (!infile.eof() && isalpha(next_char)) {
            //Written question 2 asks about the line below
	        next_word[spot] = next_char;
            ++spot;
            infile.get(next_char);
        }
        if (spot > 0) {
            next_word[spot] = '\0';
            ++word_index;
            spot = 0;
        } else {
            infile.get(next_char);
        }
    }
    return word_index;
}
