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

using namespace std;

int main(int argc, char** argv) {
    Display::Print("Hello");
    Display::NewLine();
    Display::PrintBold("Bold");
    Display::NewLine();
    Display::PrintUnderlined("Underline");
    Display::NewLine();
   
    Player *player1 = new Player();
    
    player1->addCardToHand(*(new Card(2, "Blue")));
    player1->addCardToHand(*(new Card(4, "Blue")));
    player1->addCardToHand(*(new Card(3, "Blue")));
    player1->addCardToHand(*(new Card(2, "Blue")));
    
    player1->displayHand();
    
//    list<Card> cards;
//        
//    cards.push_back(*(new Card(13)));
//    cards.push_back(*(new Card(2, "Blue")));
//    cards.push_back(*(new Card(4, "Yellow")));
//    cards.push_back(*(new Card(0)));
//
//    Display::NewLine();
//    Display::PrintCards(cards);

    Display::Clear();

//    Display::PrintCards(cards);
    
    return 0;
}