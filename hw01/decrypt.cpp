// decrypt.cpp
// Written by: Luke Randolph (lrando01)
// Date: February 5, 2023
// Purpose: This program decrypts a user-provided word
//          using a user-provided-shift Caesar cipher.

#include <iostream>
#include <string>

using namespace std;

int main()
{
//make variables for word and shift amount
    int shift_amount;
    string word;
//prompts user for word
    cout << "Enter the word that you would ";
    cout << "like to decrypt (in lowercase characters)" << endl; 
    cout << "Word to decrypt: ";
    cin >> word;
//prompt user for shift amount
    cout << "Enter the shift amount: ";
    cin >> shift_amount;
//make variables for length of word and array position 
//modulus shift amount so it is always between 0-25
    shift_amount = shift_amount % 26;
    int length_of_word = word.length();
    int next_letter_pos = 0;

    cout << "Decrypted word: ";
//make loop to change each character
    while (next_letter_pos < length_of_word) {
        char new_letter;
//set up wrapping and backwards shift
        if (word[next_letter_pos] >= ('a' + shift_amount)) {
            new_letter = word[next_letter_pos] - shift_amount;
        } else {
            new_letter = word[next_letter_pos] + 26 - shift_amount;
        }
//print out the new letter
        cout << new_letter;

        next_letter_pos = next_letter_pos + 1;
    }

    cout << endl;

    return 0;
}
