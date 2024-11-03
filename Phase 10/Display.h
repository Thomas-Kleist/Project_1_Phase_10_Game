/* 
 * File:   Display.h
 * Author: Thomas Kleist
 *
 * Created on November 2, 2024, 10:35 AM
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <list>
#include <iomanip>
#include <string>
#include "Color.h"
#include "Card.h"

class Display {
    public:
      static void BeginBold() { std::cout << "\033[1m"; }

      static void BeginUnderline() { std::cout << "\033[4m"; }

      static void BeginColor(std::string col) { std::cout << "\033[" << unsigned(COLOR[col].AsFG()) << "m"; }

      static void NewLine() { std::cout << std::endl; }

      static void EndFormat() { std::cout << "\033[0m"; }
      
      static void Clear() { NewLine(); NewLine(); NewLine(); NewLine(); NewLine(); NewLine(); NewLine(); NewLine(); }

      template <typename T> static void Print(T x) {
        std::cout << x;
      }

      template <typename T> static void PrintBold(T x) {
        Display::BeginBold();
        std::cout << x;
        Display::EndFormat();
      }

      template <typename T> static void PrintUnderlined(T x) {
        Display::BeginUnderline();
        std::cout << x;
        Display::EndFormat();
      }
      
      static void PrintCards(Card card) {
            BeginColor(card.getColor());
            Print("+----+\n");
            Print("|    |\n");
            Print("| ");
            std::cout << std::setw(2) << card.getDisplayValue();
            Print(" |\n");
            Print("|    |\n");
            Print("+----+\n");
      }
      
      static void PrintCards(std::list<Card> cards) {
            // print top
            for (Card card : cards) {
                BeginColor(card.getColor());
                Print("+----+ ");
            }
            NewLine();
            // print upper middle
            for (Card card : cards) {
                BeginColor(card.getColor());
                Print("|    | ");
            }
            NewLine();
            // print display value
            for (Card card : cards) {
                BeginColor(card.getColor());
                Print("| ");
                std::cout << std::setw(2) << card.getDisplayValue();
                Print(" | ");
            }
            NewLine();
            // print lower middle
            for (Card card : cards) {
                BeginColor(card.getColor());
                Print("|    | ");
            }
            NewLine();
            // print bottom
            for (Card card : cards) {
                BeginColor(card.getColor());
                Print("+----+ ");
            }
            NewLine();
      }
      
};

#endif /* DISPLAY_H */

