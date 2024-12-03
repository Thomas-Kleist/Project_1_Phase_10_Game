/* 
 * File:   main.cpp
 * Author: Thomas Kleist
 *
 * Created on November 2, 2024, 10:32 AM
 */

#include <cstdlib>
#include <iostream>
#include "Display.h"
#include "Game.h"

using namespace std;

int main(int argc, char** argv) {
    Display::PrintBold("Phase 10");
    Display::NewLine();

    Game *game = new Game();
        
    game->setupRound();
    
    int playerTurn = 1;
    game->turn(playerTurn);
    
    return 0;
}