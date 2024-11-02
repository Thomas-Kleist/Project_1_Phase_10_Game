/* 
 * File:   Card.cpp
 * Author: Thomas Kleist
 * 
 * Created on November 2, 2024, 11:10 AM
 */

#include <string>
#include "Card.h"

Card::Card(int faceValue) {
    this->faceValue = faceValue;
    this->color = "Black";
}

Card::Card(int faceValue, std::string colorValue) {
    this->faceValue = faceValue;
    this->color = colorValue;
}

Card::Card(const Card& orig) {
    // Copy Values
    this->faceValue = orig.faceValue;
    this->color = orig.color;
}

std::string Card::getDisplayValue() {
    // Handle Blank Card
    if (faceValue == 0) return "";
    // Handle Wild Card
    if (faceValue == 13) return "W";
    // Handle Skip Card
    if (faceValue == 14) return "S";
    // Handle Number Cards
    return std::to_string(faceValue);
}

Card::~Card() {
    
}