/* 
 * File:   Game.cpp
 * Author: Thomas Kleist
 * 
 * Created on November 2, 2024, 9:19 PM
 */

#include "Game.h"
#include "Display.h"
#include <iostream>
#include "Group.h"

Game::Game() {    
    player1 = new Player();
    player2 = new Player();
}

void Game::setupRound() {
    if (deck != NULL) delete(deck);
    deck = new Deck();
    
    deck->deal(player1);
    deck->deal(player2);
    
    
}
    

Game::~Game() {
}

void Game::drawFromPile(int player) {
    Player *currentPlayer = (player == 1)?player1:player2;
    Display::PrintUnderlined("Draw Piles");
    Display::NewLine();
    deck->drawPiles();
    Display::PrintUnderlined("Your Hand");
    Display::NewLine();
    currentPlayer->displayHand();
    Display::Print("Do you want to draw from the ");
    Display::PrintUnderlined("Draw");
    Display::Print(" pile of the ");
    Display::PrintUnderlined("Discard");
    Display::Print(" pile?");
    Display::NewLine();
    bool success = false;
    while (success == false) {
        std::string choice;
        std::cin >> choice;
        if (choice == "Draw") {
            currentPlayer->addCardToHand(deck->drawFromDrawPile());
            success = true;
        } if (choice == "Discard") {
            currentPlayer->addCardToHand(deck->drawFromDiscard());
            success = true;
        }
    }
    Display::PrintUnderlined("Your New Hand");
    Display::NewLine();
    currentPlayer->displayHand();
}

bool Game::discard(int player) {
    Player *currentPlayer = (player == 1)?player1:player2;

    Display::Print("Select card you would like to discard:");
    Display::NewLine();
    while (true) {
        int selected;
        std::cin >> selected;
        try {
            Card discardCard = currentPlayer->removeCard(selected-1);
            deck->discardCard(discardCard);
            return (discardCard.getFaceValue() == 14);
        } catch (...) {
            Display::Print("Value out of range. Select card you would like to discard");
            Display::NewLine();
        }
    }
}

bool Game::layDown(int player) {
    Player *currentPlayer = (player == 1)?player1:player2;

    Phase *phase = new Group(3);
    
    for (int i = 0; i < phase->getRequiredSize(); i++) {
        Display::Print("Select card you would like to add to ");
        phase->printType();
        Display::Print(" (Press 0 to cancel):");
        Display::NewLine();
        bool success = false;
        while (!success) {
            int selected;
            std::cin >> selected;
            if (selected == 0) {
                while (!phase->empty()) {
                    currentPlayer->addCardToHand(phase->removeCard());
                }
                return false;
            }
            try {
                Card card = currentPlayer->removeCard(selected-1);
                bool addedCard = phase->addCard(card);
                if (addedCard) {
                    Display::Print("Successfully added card to phase"); 
                    success = true;
                } else {
                    Display::Print("Could not add card");
                    currentPlayer->addCardToHand(card);
                }
                Display::NewLine();
                Display::PrintUnderlined("Your New Hand Is");
                Display::NewLine();
                currentPlayer->displayHand();
                Display::PrintUnderlined("The Phase is");
                Display::NewLine();
                phase->displayCards();
            } catch (...) {
                Display::Print("Value out of range. Select card you would like to discard");
                Display::NewLine();
            }
        }
    }
}

bool Game::turn(int player) {
    Player *currentPlayer = (player == 1)?player1:player2;

    Display::PrintBold("Player ");
    Display::PrintBold(player);
    Display::PrintBold(" Turn");
    Display::NewLine();
    
    drawFromPile(player);
    
    while (true) {
        if (currentPlayer->getLayDown() == false) { 
            Display::Print("Would you like to ");
            Display::PrintUnderlined("Lay Down");
            Display::Print(" or ");
            Display::PrintUnderlined("Discard");
            Display::Print("?");
            Display::NewLine();

            bool success = false;
            while (success == false) {
                std::string choice;
                std::getline(std::cin, choice);
                if (choice == "Lay Down") {
                    bool layDownSuccess = layDown(player);
                    
                    Display::PrintUnderlined("Your Hand");
                    Display::NewLine();
                    currentPlayer->displayHand();
                    
                    success = true;
                } if (choice == "Discard") {
                    return discard(player);
                }
            }
        } else {
            Display::Print("Would you like to ");
            Display::PrintUnderlined("Hit");
            Display::Print(" or ");
            Display::PrintUnderlined("Discard");
            Display::Print("?");
            Display::NewLine();

            bool success = false;
            while (success == false) {
                std::string choice;
                std::cin >> choice;
                if (choice == "Hit") {


                    success = true;
                } if (choice == "Discard") {
                    return discard(player);
                }
            }
        }
    }
    return false;
}
