/* 
 * File:   Phase.cpp
 * Author: Thomas Kleist
 * 
 * Created on November 3, 2024, 8:09 AM
 */

#include "Display.h"
#include "Phase.h"
#include "Card.h"

Phase::Phase(int size) {
    requiredSize = size;
}

bool Phase::addCard(Card card) {
    cards.push_back(card);
    return true;
}

Card Phase::removeCard() {
    Card toReturn = cards.front();
    cards.pop_front();
    return toReturn;
}

void Phase::printType() {
    Display::Print("Default Phase");
}


void Phase::displayCards() {
    Display::PrintCards(cards);
    Display::BeginColor("Black");
    Display::NewLine();
}