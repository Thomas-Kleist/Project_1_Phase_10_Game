/* 
 * File:   main.cpp
 * Author: Thomas Kleist
 *
 * Created on November 2, 2024, 10:50 AM
 */

#include "Color.h"

#include <map>
#include <string>

std::map<std::string, Color> COLOR = Color::CreateColorMap();

Color::Color(uint8_t val) : inner(val) {
}


Color::Color(const Color& orig) {
}

Color::~Color() {
}

// Creates a map of all of the possible 4-bit ANSI colors.
std::map<std::string, Color> Color::CreateColorMap() {
    std::map<std::string, Color> m;
    m["Black"] = Color(0);
    m["Red"] = Color(1);
    m["Green"] = Color(2);
    m["Yellow"] = Color(3);
    m["Blue"] = Color(4);
    m["Magenta"] = Color(5);
    m["Cyan"] = Color(6);
    m["White"] = Color(7);

    return m;
}