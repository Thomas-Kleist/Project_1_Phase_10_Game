/* 
 * File:   Player.h
 * Author: Thomas Kleist
 *
 * Created on November 2, 2024, 3:06 PM
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <list>
#include "Card.h"

class Player {
public:
    Player();
    virtual ~Player();
    
    void sortHand();
    void addCardToHand(Card);
    void displayHand();
    Card removeCard(int);
    void endRound();
    bool getLayDown() { return layDown; }
    void setLayDown() { layDown = true; };
    int getCurrentPhase() { return phase; }
    void increasePhase() { phase++; }
    int getScore() { return score; }
    bool handEmpty() { return hand.empty(); }
private:
    int score;
    int phase;
    std::list<Card> hand;
    bool layDown;
};

#endif /* PLAYER_H */

