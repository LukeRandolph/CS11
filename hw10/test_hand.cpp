/*
 * test_hand.cpp
 * Written by: Dave Lillethun
 * Edited by: Richard Townsend
 * Date last edited for starter code: 11/9/2022
 * Purpose: Test the methods defined by the hand class.
 *
 */

//NOTE: We only have to include hand.h (and not card.h) because hand.h already
//has a #include "card.h" inside of it!
#include "hand.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
   /********************************************************************
   * Read the first 5 numbers from the deck file into an array so we can
   * compare it to an actual Hand object.
   ********************************************************************/

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " filename" << endl;
        exit(EXIT_FAILURE);
    }
    string deckFileName = argv[1];

    ifstream deckFile(deckFileName);
    if (deckFile.fail()) {
        cerr << "Failed to open deck file: " << deckFileName << endl;
        exit(EXIT_FAILURE);
    }

    // Read the first 5 numbers into an array for testing purposes
    int deck_contents[Hand::HAND_SIZE];
    for (int i = 0; i < Hand::HAND_SIZE; i++) {
        deckFile >> deck_contents[i];

        if (deckFile.eof()) {
            cerr << "File does not contain " << Hand::HAND_SIZE << " cards!"
                 << endl;
            exit(EXIT_FAILURE);
        } else if (deckFile.fail()) {
            cerr << "Failed to read from file: " << deckFileName << endl;
            exit(EXIT_FAILURE);
        }
    }

   /********************************************
   * Build the actual hand and run our tests.
   ********************************************/

    Hand hand(new Card(deck_contents[0]), new Card(deck_contents[1]),
              new Card(deck_contents[2]), new Card(deck_contents[3]),
              new Card(deck_contents[4]));
    
    Card *newCard = new Card(6);
    cout << newCard->getNum() << endl;
    hand.replaceCard(newCard);




    if(hand.isWinningHand()){
        cout << "passes" << endl;
    }else{
    cout << "This hand is not a winner!" << endl;
    }

    cout << "If it says passes, "
         << "then index 4 was chosen on deck2.txt!" << endl;
    return 0;
}
