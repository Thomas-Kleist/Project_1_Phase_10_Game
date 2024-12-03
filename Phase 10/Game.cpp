/* 
 * File:   Game.cpp
 * Author: Thomas Kleist
 * 
 * Created on November 2, 2024, 9:19 PM
 */

#include "Game.h"
#include <cstdlib>
#include "Display.h"
#include <iostream>
#include "Group.h"
#include "Run.h"
#include "ColorPhase.h"

Game::Game() {    
    player1 = new Player();
    player2 = new Player();
    
    phaseNameMap.insert("0", "You are on Phase 1: 2 Sets of 3");
    phaseNameMap.insert("1", "You are on Phase 2: 1 Set of 3 + 1 Run of 4");
    phaseNameMap.insert("2", "You are on Phase 3: 1 Set of 4 + 1 Run of 4");
    phaseNameMap.insert("3", "You are on Phase 4: 1 Run of 7");
    phaseNameMap.insert("4", "You are on Phase 5: 1 Run of 8");
    phaseNameMap.insert("5", "You are on Phase 6: 1 Run of 9");
    phaseNameMap.insert("6", "You are on Phase 7: 2 Sets of 4");
    phaseNameMap.insert("7", "You are on Phase 8: 7 Cards of 1 Color");
    phaseNameMap.insert("8", "You are on Phase 9: 1 Set of 5 + 1 Set of 2");
    phaseNameMap.insert("9", "You are on Phase 10: 1 Set of 5 + 1 Set of 3");
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
    Display::PrintUnderlined("Active Phases");
    Display::NewLine();
    printActivePhases();
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

bool Game::fillPhase(int player, Phase *phase) {
    Player *currentPlayer = (player == 1)?player1:player2;

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
    return true;
}

bool Game::layDown(int player) {
    Player *currentPlayer = (player == 1)?player1:player2;
    
    std::list<Phase*> phases = getPhase(currentPlayer->getCurrentPhase());
    
    std::list<Phase*>::iterator it = phases.begin();
       
    while (it != phases.end()) {
        Display::Print("Filling New Phase");
        Display::NewLine();
        bool success = fillPhase(player, *it);
        if (!success) {
            while (it != phases.begin()) {
                while (!(*it)->empty()) {
                    currentPlayer->addCardToHand((*it)->removeCard());
                }
                it--;
            }
            while (!(*it)->empty()) {
                currentPlayer->addCardToHand((*it)->removeCard());
            }            
            return false;
        }
        it++;
    }
    
    while (!phases.empty()) {
        activePhases.push_back(phases.front());
        phases.pop_front();
    }
    
    return true;
}

bool Game::hit(int player) {
    Player *currentPlayer = (player == 1)?player1:player2;
    
    std::set<std::string> availableToPlay;
    for (Phase *phase : activePhases) {
        phase->addAvailableCards(availableToPlay);
    }
    Display::Print("The available cards to play are: ");
    for (std::string move : availableToPlay)
    {
        Display::Print(move);
        Display::Print(", ");
    }
    Display::NewLine();
    

    Display::Print("Select Phase to Hit On (Press 0 to cancel):");
    Display::NewLine();
    
    int phaseSelected;
    std::cin >> phaseSelected;
    if (phaseSelected == 0) {
        return false;
    }
    
    phaseSelected--;
    if (phaseSelected < 0 || phaseSelected >= activePhases.size()) {
        Display::Print("Selected Phase is out of range");
        return false;
    }
    
    std::list<Phase*>::iterator it = activePhases.begin();
    std:advance(it, phaseSelected);
    
    Display::Print("Select card you would like to hit (Press 0 to cancel):");
    Display::NewLine();

    int cardSelected;
    std::cin >> cardSelected;
    if (cardSelected == 0) {
        return false;
    }
    try {
        Card card = currentPlayer->removeCard(cardSelected-1);
        bool addedCard = (*it)->addCard(card);
        if (addedCard) {
            Display::Print("Successfully added card to phase"); 
            Display::NewLine();
            return true;
        } else {
            Display::Print("Could not add card");
            Display::NewLine();
            currentPlayer->addCardToHand(card);
            return false;
        }
    } catch (...) {
        return false;
    }
}

void Game::turn(int player) {
    Player *currentPlayer = (player == 1)?player1:player2;

    Display::PrintBold("Player ");
    Display::PrintBold(player);
    Display::PrintBold(" Turn");
    Display::NewLine();
    if (!currentPlayer->getLayDown()) {
        printPhase(currentPlayer->getCurrentPhase());
    }
    
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
                    
                    if (layDownSuccess) {
                        currentPlayer->increasePhase();
                        currentPlayer->setLayDown();
                        
                        Display::Print("Phase Laid Down");
                        Display::NewLine();
                    } else {
                        Display::Print("Phase Not Laid Down");
                        Display::NewLine();
                    }
                    
                    Display::PrintUnderlined("Active Phases");
                    Display::NewLine();
                    printActivePhases();
                    Display::PrintUnderlined("Your Hand");
                    Display::NewLine();
                    currentPlayer->displayHand();
                    
                    success = true;
                } if (choice == "Discard") {
                    bool skip = discard(player);
                    if (!skip) {
                        turn((player==1)?2:1);
                        return;
                    } else {
                        turn(player);
                        return;
                    }
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
                    hit(player);

                    Display::PrintUnderlined("Active Phases");
                    Display::NewLine();
                    printActivePhases();
                    Display::PrintUnderlined("Your Hand");
                    Display::NewLine();
                    currentPlayer->displayHand();
                    
                    if (currentPlayer->handEmpty()) {
                        endRound();
                        turn((player==1)?2:1);
                        return;
                    }
                    
                    success = true;
                } if (choice == "Discard") {
                    bool toReturn = discard(player);
                    if (currentPlayer->handEmpty()) endRound();
                    if (!toReturn) {
                        turn((player==1)?2:1);
                        return;
                    } else {
                        turn(player);
                        return;
                    }
                }
            }
        }
    }
    return;
}

void Game::endRound() {
    player1->endRound();
    player2->endRound();
    
    activePhases.clear();
    
    if (player1->getCurrentPhase() == 10 && player2->getCurrentPhase() == 10) {
        if (player1->getScore() < player2->getScore()) {
            Display::Print("Player 1 Wins!!!!!");
            exit(0);
        } else {
            Display::Print("Player 2 Wins!!!!!");
            exit(0);
        }
    } else if (player1->getCurrentPhase() == 10) {
        Display::Print("Player 1 Wins!!!!!");
        exit(0);
    } else if (player2->getCurrentPhase() == 10) {
        Display::Print("Player 2 Wins!!!!!");
        exit(0);
    }
    
    Display::NewLine();
    Display::PrintBold("Round Completed");
    Display::NewLine();
    Display::Print("Player 1 Score: ");
    Display::Print(player1->getScore());
    Display::NewLine();
    Display::Print("Player 1 Phase: ");
    Display::Print(player1->getCurrentPhase()+1);
    Display::NewLine();
    Display::NewLine();
    Display::Print("Player 2 Score: ");
    Display::Print(player2->getScore());
    Display::NewLine();
    Display::Print("Player 2 Phase: ");
    Display::Print(player2->getCurrentPhase()+1);
    Display::NewLine();
    
    setupRound();
}

void Game::printPhase(int phase) {
    Display::Print(phaseNameMap.get(std::to_string(phase)));
    Display::NewLine();
}

void Game::printActivePhases() {
    int count = 1;
    for (Phase *phase : activePhases) {
        Display::Print(count);
        Display::Print(". ");
        phase->printType();
        Display::NewLine();
        phase->displayCards();
        count++;
    }
}

std::list<Phase*> Game::getPhase(int phase) {
    std::list<Phase*> phases;
    switch(phase) {
        case 0:
            phases.push_back(new Group(3));
            phases.push_back(new Group(3));
            break;
        case 1:
            phases.push_back(new Group(3));
            phases.push_back(new Run(4));
            break;
        case 2:
            phases.push_back(new Group(4));
            phases.push_back(new Run(4));
            break;
        case 3:
            phases.push_back(new Run(7));
            break;
        case 4:
            phases.push_back(new Run(8));
            break;
        case 5:
            phases.push_back(new Run(9));
            break;
        case 6:
            phases.push_back(new Group(4));
            phases.push_back(new Group(4));
            break;
        case 7:
            phases.push_back(new ColorPhase(7));
            break;
        case 8:
            phases.push_back(new Group(5));
            phases.push_back(new Group(2));
            break;
        case 9:
            phases.push_back(new Group(5));
            phases.push_back(new Group(3));
            break;
        default:
            // code block
            break;
    }
    return phases;
}