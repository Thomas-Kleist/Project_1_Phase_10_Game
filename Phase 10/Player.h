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
    Player(const Player& orig);
    virtual ~Player();
    
    void sortHand();
    void addCardToHand(Card);
    void displayHand();
    Card removeCard(int);
private:
    int score;
    int phase;
    std::list<Card> hand;
};

#endif /* PLAYER_H */

