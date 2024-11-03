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
//    Display::Print("Hello");
//    Display::NewLine();
//    Display::PrintBold("Bold");
//    Display::NewLine();
//    Display::PrintUnderlined("Underline");
//    Display::NewLine();
   
    Deck *deck = new Deck();
    
    Player *player1 = new Player();
    deck->deal(player1);

//    Display::PrintBold("Player 1");
//    Display::NewLine();
//    player1->displayHand();
    
    Player *player2 = new Player();
    deck->deal(player2);

//    Display::PrintBold("Player 2");
//    Display::NewLine();
//    player2->displayHand();
    
//    Display::PrintBold("Draw Piles");
//    Display::NewLine();
//    deck->drawPiles();
    
    Display::PrintBold("Player 1 Turn");
    Display::NewLine();
    Display::PrintUnderlined("Draw Piles");
    Display::NewLine();
    deck->drawPiles();
    Display::PrintUnderlined("Your Hand");
    Display::NewLine();
    player1->displayHand();
    Display::Print("Do you want to draw from the ");
    Display::PrintUnderlined("Draw");
    Display::Print(" pile of the ");
    Display::PrintUnderlined("Discard");
    Display::Print(" pile?");
    Display::NewLine();
    bool success = false;
    while (success == false) {
        string choice;
        cin >> choice;
        if (choice == "Draw") {
            player1->addCardToHand(deck->drawFromDrawPile());
            success = true;
        } if (choice == "Discard") {\
            player1->addCardToHand(deck->drawFromDiscard());
            success = true;
        }
    }
    Display::PrintUnderlined("Your New Hand");
    Display::NewLine();
    player1->displayHand();
    Display::Print("Select card you would like to discard:");
    Display::NewLine();
    success = false;
    while (success == false) {
        int selected;
        cin >> selected;
        try {
            deck->discardCard(player1->removeCard(selected-1));
            success = true;
        } catch (...) {
            Display::Print("Value out of range. Select card you would like to discard");
            Display::NewLine();
        }
    }
    deck->drawPiles();
    
//    try {
//        Display::PrintCards(player1->removeCard(2));
//    } catch (...) {
//        Display::Print("Index out of bounds");
//        Display::NewLine();
//    }
//    
//    player1->displayHand();
//
//    Display::Clear();
    
    return 0;
}