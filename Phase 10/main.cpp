/* 
 * File:   main.cpp
 * Author: Thomas Kleist
 *
 * Created on November 2, 2024, 10:32 AM
 */

#include <cstdlib>
#include <iostream>
#include <list>
#include <algorithm>
#include "Display.h"
#include "Card.h"
#include "Player.h"
#include "Deck.h"
#include "Game.h"

using namespace std;

int main(int argc, char** argv) {
    Display::PrintBold("Phase 10");
    Display::NewLine();

    Game *game = new Game();
        
    game->setupRound();
    
    int playerTurn = 1;
    while (true) {
        bool skip = game->turn(playerTurn);
        if (!skip) {
            playerTurn = (playerTurn==1)?2:1;
        }
    }
    
    return 0;
}