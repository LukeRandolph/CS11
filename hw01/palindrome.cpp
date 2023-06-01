// palindrome.cpp
// Written by: Luke Randolph (lrando01)
// Date: February 5, 2023
// Purpose: This program decides whether a word is a palindrome
// or not, or if it is close to one


#include <string>
#include <iostream>
using namespace std;

int main() {
//make varaibles for word 
//create a bool statement to end loop when not palindrome
    string word;
    bool palindrome = true;
    cout << "Greetings! I am the palindrome decider!" << endl;
//make a while loop to run the code until palindrome returns false
    while (palindrome) {
//prompt user for word, make length variables and holder variables
        cout << "Please enter a word: ";
        cin >> word;
        int length_of_word = word.length();
        int count = 0;
        int special_count = 0;
//make a for loop to add to our holder variables the correct amounts
//will run until it checks half of the word's characters, odd doesn't matter
        for (int i=0; i<length_of_word/2; i++) {
            if (word[i] == word[length_of_word - 1 - i]) {
                if (i < 3) {
                    special_count++;
                }
                count++;
            }
        }
//where our holder variables determine the correct print statement
        if (count >= length_of_word/2) {
            cout << "Your word is a palindrome! Fantastic!" << endl;
        } else if (special_count == 3) {
            cout << "Not quite a palindrome, but close enough." << endl;
        } else {
            cout << "Your word is NOT a palindrome. Thanks anyway!" << endl;
            palindrome = false;
        }

    }

    return 0;
}