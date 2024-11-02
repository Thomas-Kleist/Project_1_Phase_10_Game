/* 
 * File:   Color.h
 * Author: Thomas Kleist
 *
 * Created on November 2, 2024, 10:38 AM
 */

#ifndef COLOR_H
#define COLOR_H

#include <map>
#include <string>
#include <cinttypes>

/* This class represents a Color -- specifically a 4 bit color based on ANSI escape sequences. See https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences for more info */
class Color {
public:
    Color() { };
    //Color(std::string);
    Color(uint8_t);
    Color(const Color& orig);

    virtual ~Color();

    uint8_t AsFG() { return inner + 30; }
    uint8_t AsBG() { return inner + 40; }
    static std::map<std::string, Color> CreateColorMap();


    uint8_t inner;
};

extern std::map<std::string, Color> COLOR;

#endif /* COLOR_H */

