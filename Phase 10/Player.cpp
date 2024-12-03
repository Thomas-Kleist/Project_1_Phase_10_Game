/* 
 * File:   Player.cpp
 * Author: Thomas Kleist
 * 
 * Created on November 2, 2024, 3:06 PM
 */

#include "Player.h"
#include "Display.h"
#include <list>
#include <algorithm>    // std::random_shuffle
#include <random>
#include <iostream>

Player::Player() {
    score = 0;
    phase = 0;
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

// Function to merge two sorted lists
std::list<Card> merge(std::list<Card>& left, std::list<Card>& right) {
    std::list<Card> result;
    auto itLeft = left.begin();
    auto itRight = right.begin();

    // Merge the two lists into the result list
    while (itLeft != left.end() && itRight != right.end()) {
        if (*itLeft < *itRight) {
            result.push_back(*itLeft);
            ++itLeft;
        } else {
            result.push_back(*itRight);
            ++itRight;
        }
    }

    // Append any remaining elements from left or right
    result.insert(result.end(), itLeft, left.end());
    result.insert(result.end(), itRight, right.end());

    return result;
}

// Function to split a list into two halves
void split(std::list<Card>& original, std::list<Card>& left, std::list<Card>& right) {
    auto it = original.begin();
    std::advance(it, original.size() / 2);
    left.splice(left.end(), original, original.begin(), it);
    right.splice(right.end(), original, it, original.end());
}

// Function to perform merge sort on a list
std::list<Card> mergeSort(std::list<Card> lst) {
    if (lst.size() <= 1) {
        return lst;  // Base case: if the list has 1 or 0 elements, it's already sorted
    }

    std::list<Card> left, right;
    split(lst, left, right);  // Split the list into two halves

    // Recursively sort the two halves and merge them
    left = mergeSort(left);
    right = mergeSort(right);

    // Merge the two sorted halves
    return merge(left, right);
}

struct Node {
    Card* data;
    Node* left;
    Node* right;

    Node(Card *value) {
        data = value;
        left = right = nullptr;
    }
};

Node* insertTree(Node *root, Card *data) {
    if (root == nullptr) {
        root = new Node(data);
        return root;
    }
    
    if (colorCompare(*data, *(root->data))) {
        root->left = insertTree(root->left, data);
    } else {
        root->right = insertTree(root->right, data);
    }
    
    return root;
}

std::list<Card> readTree(Node *root, std::list<Card> lst) {
    if (root == nullptr) {
        return lst;
    }
    
    lst = readTree(root->left, lst);
    lst.push_back(*(root->data));
    lst = readTree(root->right, lst);
    return lst;
}

std::list<Card> treeSort(std::list<Card> lst) {
    Node *root = nullptr;
    
    for (std::list<Card>::iterator it = lst.begin(); it != lst.end(); ++it) {
        root = insertTree(root, &(*it));
    }
    std::cout << std::endl;
    
    std::list<Card> newList;
    lst = readTree(root, newList);
        
    return lst;
}



void Player::sortHand() {
    if (phase == 7) {
        hand = treeSort(hand);
    } else {
        hand = mergeSort(hand);
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
    if (pos < 0 || pos >= hand.size()) throw "Out of Range";
    std::list<Card>::iterator it = hand.begin();
    std:advance(it, pos);
    Card toReturn = *it;
    hand.erase(it);
    return toReturn;
}

void Player::endRound() {
    while (!hand.empty()) {
        score += hand.front().getPointValue();
        hand.pop_front();
    }
    layDown = false;
}
