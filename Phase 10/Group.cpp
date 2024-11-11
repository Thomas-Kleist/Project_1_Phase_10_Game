/* 
 * File:   Group.cpp
 * Author: Thomas Kleist
 * 
 * Created on November 3, 2024, 9:56 AM
 */

#include "Group.h"
#include "Display.h"
#include <iostream>

bool Group::addCard(Card card) {
    // Do not add skip cards
    if (card.getFaceValue() == 14) return false;
    
    if (cards.empty()) {
        // If adding a wild card, ask for which value to use
        if (card.getFaceValue() == 13) {
            int numSelected = 0;
            Display::Print("Select which number you want the wild card to have:");
            Display::NewLine();
            while (!(numSelected >= 1 && numSelected <= 12))
                std::cin >> numSelected;
            card.setPhaseValue(numSelected);
        }
        cards.push_back(card);
        return true;
    }
    
    if (card.getFaceValue() == 13) {
        card.setPhaseValue(cards.front().getPhaseValue());
        cards.push_back(card);
        return true;
    }
    
    if (card.getPhaseValue() == cards.front().getPhaseValue()) {
        cards.push_back(card);
        return true;
    }
    
    return false;
}

Group::~Group() {
}

