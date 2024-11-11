/* 
 * File:   Phase.h
 * Author: Thomas Kleist
 *
 * Created on November 3, 2024, 8:09 AM
 */

#ifndef PHASE_H
#define PHASE_H

#include "Card.h"
#include <list>
#include <set>
#include <string>

class Phase {
public:
    Phase(int);
    void setRequiredSize(int size) { requiredSize = size; }
    int getRequiredSize() { return requiredSize; }
    void displayCards();
    virtual bool addCard(Card);
    virtual void printType();
    bool empty() { return cards.empty(); }
    Card removeCard();
    virtual void addAvailableCards (std::set<std::string>& setOfCards) {};
protected:
    int requiredSize;
    std::list<Card> cards;
};

#endif /* PHASE_H */