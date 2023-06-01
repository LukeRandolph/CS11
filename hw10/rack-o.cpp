/*
 * rack-o.cpp
 * Written by: Dave Lillethun
 * Edited by: Richard Townsend
 * Date last edited for starter code: 11/9/2022
 * Purpose: Provide the main() function that drives the rack-o game
 *
 */

#include "game.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " filename" << endl;
        exit(EXIT_FAILURE);
    }

    Game racko(argv[1]);
    racko.play();

    return 0;
}
