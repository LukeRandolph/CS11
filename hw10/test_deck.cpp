/*
 * test_deck.cpp
 * Written by: Dave Lillethun
 * Edited by: Richard Townsend
 * Date last edited for starter code: 11/8/2022
 * Purpose: Test the methods defined by the deck class.
 *
 */

//NOTE: We only have to include deck.h (and not card.h) because deck.h already
//has a #include "card.h" inside of it!
#include "deck.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
   /****************************
   * Read the whole deck file into an array so we can access any card we want
   * (not just the top element)
   ******************************/

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

    // Read all the numbers into an array for testing purposes
    int deck_contents[Deck::MAX_DECK_SIZE];
    for (int i = 0; i < Deck::MAX_DECK_SIZE; i++) {
        deckFile >> deck_contents[i];

        if (deckFile.eof()) {
            cerr << "File does not contain " << Deck::MAX_DECK_SIZE << " cards!"
                 << endl;
            exit(EXIT_FAILURE);
        } else if (deckFile.fail()) {
            cerr << "Failed to read from file: " << deckFileName << endl;
            exit(EXIT_FAILURE);
        }
    }

   /********************************************
   * Build the actual deck and run our tests.
   ********************************************/

    // Build the actual Deck object with the contents of the deck file
    Deck deck(deckFileName);

    // Try drawing every card, making sure we aren't empty at any point and that
    // the next card drawn has a number equivalent to the next spot in the
    // deck_contents array.
    for (int i = 0; i < Deck::MAX_DECK_SIZE; i++) {
        if (deck.isEmpty()) {
            cout << "FAILED: deck is prematurely empty at card " << i << endl;
        }

        Card *card = deck.draw();

        if (card == NULL) {
            cout << "FAILED: card " << i
                 << " returned NULL!  Expected: " << deck_contents[i] << endl;

        } else if (card->getNum() != deck_contents[i]) {
            cout << "FAILED: card " << i << " did not match! Got "
                 << card->getNum() << " but expected " << deck_contents[i]
                 << endl;
        }

        // Clean-up after ourselves: delete each card after it's been drawn
        if (card != NULL) {
            delete card;
        }
    }

    // Check that the deck is empty after drawing all the cards
    if (!deck.isEmpty()) {
        cout << "FAILED: deck is *not* empty after drawing "
             << Deck::MAX_DECK_SIZE << " cards!" << endl;
    }

    cout << "Failed tests are listed above. If there is no output, "
         << "then it all succeeded!" << endl;
    return 0;
}
