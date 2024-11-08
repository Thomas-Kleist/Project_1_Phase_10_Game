/* 
 * File:   Deck.cpp
 * Author: Thomas Kleist
 * 
 * Created on November 2, 2024, 5:10 PM
 */

#include <algorithm>
#include "Deck.h"
#include "Player.h"
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include "Display.h"

Deck::Deck() {
    // Push number cards
    for (int i = 1; i <= 12; i++) {
        drawPile.push_front(*(new Card(i, "Blue")));
        drawPile.push_front(*(new Card(i, "Blue")));
        drawPile.push_front(*(new Card(i, "Green")));
        drawPile.push_front(*(new Card(i, "Green")));
        drawPile.push_front(*(new Card(i, "Red")));
        drawPile.push_front(*(new Card(i, "Red")));
        drawPile.push_front(*(new Card(i, "Yellow")));
        drawPile.push_front(*(new Card(i, "Yellow")));
    }
    for (int i = 0; i < 8; i++) {
        drawPile.push_front(*(new Card(13)));
    }
    for (int i = 0; i < 4; i++) {
        drawPile.push_front(*(new Card(14)));
    }
    shuffleDraw();
    discardPile.push(drawPile.front());
    drawPile.pop_front();
}

Deck::Deck(const Deck& orig) {
}

Deck::~Deck() {
}

void Deck::shuffleDraw() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::shuffle(drawPile.begin(), drawPile.end(), std::default_random_engine(seed));
}

void Deck::deal(Player *player) {
    for (int i = 0; i < 10; i++) {
        player->addCardToHand(drawPile.front());
        drawPile.pop_front();
    }
}

void Deck::drawPiles() {
    std::list<Card> toDisplay;
    toDisplay.push_front(discardPile.top());
    toDisplay.push_front(*(new Card(0)));
    Display::PrintCards(toDisplay);
    Display::BeginColor("Black");
    Display::Print(" Draw  Discard");
    Display::NewLine();
}


Card Deck::drawFromDiscard() {
    Card toReturn = discardPile.top();
    discardPile.pop();
    return toReturn;
}

Card Deck::drawFromDrawPile() {
    Card toReturn = drawPile.front();
    drawPile.pop_front();
    
    if (drawPile.empty()) {
        while(discardPile.empty() == false) {
            drawPile.push_front(discardPile.top());
            discardPile.pop();
        }
        shuffleDraw();
        discardPile.push(drawPile.front());
        drawPile.pop_front();
    }
    
    return toReturn;
}

void Deck::discardCard(Card card) {
    discardPile.push(card);
}

