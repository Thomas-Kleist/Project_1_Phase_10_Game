/* 
 * File:   Card.h
 * Author: Thomas Kleist
 * 
 *
 * Created on November 2, 2024, 11:10 AM
 */

#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
public:
    // Only to be used for wilds, skips, or blank
    Card(int faceValue);
    Card(int faceValue, std::string colorValue);
    Card(const Card& orig);
    std::string getColor() { return color; }
    int getColorNum() { if (color == "Red") return 0; else if (color == "Blue") return 1; else if (color == "Green") return 2; else if (color == "Yellow") return 3; else return 4; }
    std::string getDisplayValue();
    int getFaceValue() { return faceValue; }
    int getPointValue() {if (faceValue <= 12) return 5; if (faceValue == 13) return 25; if (faceValue == 14) return 15; }
    void setPhaseValue(int value) { phaseValue = value; }
    int getPhaseValue() { return phaseValue; }
    ~Card();
private:
    int faceValue;
    std::string color;
    int phaseValue;
};

#endif /* CARD_H */

