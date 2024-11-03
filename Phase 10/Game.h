/* 
 * File:   Game.h
 * Author: Thomas Kleist
 *
 * Created on November 2, 2024, 9:19 PM
 */

#ifndef GAME_H
#define GAME_H

#include "Deck.h"
#include "Player.h"

class Game {
public:
    Game();
    virtual ~Game();
    bool turn(int);
    void setupRound();
    void endRound();
    void drawFromPile(int);
    bool discard(int);
    bool layDown(int);
private:
    Player *player1;
    Player *player2;
    Deck *deck;
};

#endif /* GAME_H */

