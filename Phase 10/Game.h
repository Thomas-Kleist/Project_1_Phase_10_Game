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
#include "Phase.h"
#include <list>
#include "HashMap.h"
#include <string>

class Game {
public:
    Game();
    virtual ~Game();
    void turn(int);
    void setupRound();
    void endRound();
    void drawFromPile(int);
    bool discard(int);
    bool fillPhase(int, Phase*);
    bool layDown(int);
    bool hit(int);
    void printPhase(int);
    void printActivePhases();
    std::list<Phase*> getPhase(int);
private:
    Player *player1;
    Player *player2;
    Deck *deck;
    std::list<Phase*> activePhases;
    HashMap<std::string> phaseNameMap;
};

#endif /* GAME_H */

