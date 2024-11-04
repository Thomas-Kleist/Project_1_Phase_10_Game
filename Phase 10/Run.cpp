/* 
 * File:   Run.cpp
 * Author: Thomas
 * 
 * Created on November 3, 2024, 1:43 PM
 */

#include "Run.h"
#include "Display.h"
#include <iostream>
#include <string>

bool Run::addCard(Card card) {
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
        Display::Print("Would you like to add this wild to the ");
        Display::PrintUnderlined("Front");
        Display::Print(" or ");
        Display::PrintUnderlined("Back");
        Display::Print("?");
        Display::NewLine();
        
        bool success = false;
        while (success == false) {
            std::string choice;
            std::cin >> choice;
            if (choice == "Front") {
                if (cards.front().getPhaseValue() > 1) {
                    card.setPhaseValue(cards.front().getPhaseValue()-1);
                    cards.push_front(card);
                    return true;
                }
                return false;
            } 
            if (choice == "Back") {
                if (cards.back().getPhaseValue() < 12) {
                    card.setPhaseValue(cards.back().getPhaseValue()+1);
                    cards.push_back(card);
                    return true;
                }
                return false;     
            }
        }
    }
    
    if (card.getPhaseValue() == cards.front().getPhaseValue()-1) {
        cards.push_front(card);
        return true;
    }
    
    if (card.getPhaseValue() == cards.back().getPhaseValue()+1) {
        cards.push_back(card);
        return true;
    }
    
    return false;
}

void Run::printType() {
    Display::Print("Run of ");
    Display::Print(requiredSize);
}

Run::~Run() {
}

