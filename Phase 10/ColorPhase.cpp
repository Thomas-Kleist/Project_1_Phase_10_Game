/* 
 * File:   ColorPhase.cpp
 * Author: Thomas Kleist
 * 
 * Created on November 3, 2024, 3:09 PM
 */

#include "ColorPhase.h"
#include "Display.h"

ColorPhase::~ColorPhase() {
}

bool ColorPhase::addCard(Card card) {
    // Do not add skip cards
    if (card.getFaceValue() == 14) return false;
    
    if (cards.empty()) {
        // If adding a wild card, ask for which value to use
        if (card.getFaceValue() == 13) {
            std::string colorSel = "";
            Display::Print("Select which color you would like the wild card to be (Red, Blue, Green, or Yellow):");
            Display::NewLine();
            while (!(colorSel == "Red" || colorSel == "Blue" || colorSel == "Green" || colorSel == "Yellow"))
                std::cin >> colorSel;
            color = colorSel;
        } else {
            color = card.getColor();
        }
        cards.push_back(card);
        return true;
    }
    
    if (card.getFaceValue() == 13) {
        cards.push_back(card);
        return true;
    }
    
    if (card.getColor() == color) {
        cards.push_back(card);
        return true;
    }
    
    return false;
}

void ColorPhase::printType() {
    Display::Print(requiredSize);
    Display::Print(" Cards of One Color");
}

