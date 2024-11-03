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

using namespace std;

int main(int argc, char** argv) {
    Display::Print("Hello");
    Display::NewLine();
    Display::PrintBold("Bold");
    Display::NewLine();
    Display::PrintUnderlined("Underline");
    Display::NewLine();
   
    Deck *deck = new Deck();
    deck->shuffleDraw();
    
    Player *player1 = new Player();
    deck->deal(player1);

    Display::PrintBold("Player 1");
    Display::NewLine();
    player1->displayHand();
    
    Player *player2 = new Player();
    deck->deal(player2);

    Display::PrintBold("Player 2");
    Display::NewLine();
    player2->displayHand();
    
    try {
        Display::PrintCards(player1->removeCard(2));
    } catch (...) {
        Display::Print("Index out of bounds");
        Display::NewLine();
    }
    
    player1->displayHand();

    Display::Clear();
    
    return 0;
}