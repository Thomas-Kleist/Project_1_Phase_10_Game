/* 
 * File:   Player.cpp
 * Author: tfkbr
 * 
 * Created on November 2, 2024, 3:06 PM
 */

#include "Player.h"
#include "Display.h"
#include <list>
#include <algorithm>    // std::random_shuffle
#include <random>


Player::Player() {
    score = 0;
    phase = 1;
    layDown = false;
}

Player::~Player() {
}

bool cardCompare(Card &card1, Card &card2) {
    if (card1.getFaceValue() < card2.getFaceValue()) return true;
    if (card1.getFaceValue() == card2.getFaceValue() && card1.getColorNum() < card2.getColorNum()) return true;
    return false;
}

bool colorCompare(Card &card1, Card &card2) {
    if (card1.getColorNum() < card2.getColorNum()) return true;
    if (card1.getColorNum() == card2.getColorNum() && card1.getFaceValue() < card2.getFaceValue()) return true;
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
    Display::BeginColor("Black");
    for (int i = 0; i < hand.size(); i++) std::cout << "  " << std::setw(2) << i+1 << "   ";
    Display::NewLine();
}

Card Player::removeCard(int pos) {
    if (pos < 0 || pos > hand.size()) throw 0;
    std::list<Card>::iterator it = hand.begin();
    std:advance(it, pos);
    Card toReturn = *it;
    hand.erase(it);
    return toReturn;
}