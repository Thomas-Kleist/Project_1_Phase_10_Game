/* 
 * File:   Player.cpp
 * Author: tfkbr
 * 
 * Created on November 2, 2024, 3:06 PM
 */

#include "Player.h"
#include "Display.h"

Player::Player() {
    score = 0;
    phase = 1;
}

Player::Player(const Player& orig) {
}

Player::~Player() {
}

bool cardCompare(Card &card1, Card &card2) {
    if (card1.getFaceValue() < card2.getFaceValue()) return true;
    if (card1.getFaceValue() == card2.getFaceValue() && card1.getColorNum() < card2.getColorNum()) return true;
    return false;
}

bool colorCompare(Card &card1, Card &card2) {
    if (card1.getFaceValue() == card2.getFaceValue() && card1.getColorNum() < card2.getColorNum()) return true;
    if (card1.getFaceValue() < card2.getFaceValue()) return true;
    return false;
}

void Player::sortHand() {
    if (phase == 7) {
        hand.sort(colorCompare);
    } else {
        hand.sort(cardCompare);
    }
}

void Player::addCardToHand(Card card) {
    hand.push_back(card);
    sortHand();
}

void Player::displayHand() {
    Display::PrintCards(hand);
}