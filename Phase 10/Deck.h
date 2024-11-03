/* 
 * File:   Deck.h
 * Author: Thomas Kleist
 *
 * Created on November 2, 2024, 5:10 PM
 */

#ifndef DECK_H
#define DECK_H

#include <deque>
#include <stack>
#include "Card.h"
#include "Player.h"

class Deck {
public:
    Deck();
    Deck(const Deck& orig);
    virtual ~Deck();
    
    void shuffleDraw();
    void deal(Player*);
    void drawPiles();
    Card drawFromDiscard();
    Card drawFromDrawPile();
    void discardCard(Card);
    
private:
    std::deque<Card> drawPile;
    std::stack<Card> discardPile;
};

#endif /* DECK_H */

