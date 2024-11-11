/* 
 * File:   ColorPhase.h
 * Author: Thomas Kleist
 *
 * Created on November 3, 2024, 3:09 PM
 */

#ifndef COLORPHASE_H
#define COLORPHASE_H

#include <string>
#include "Phase.h"

class ColorPhase : public Phase {
public:
    explicit ColorPhase(int x) : Phase(x) { }
    virtual ~ColorPhase();
    bool addCard(Card);
    void printType() override;
private:
    std::string color;
};

#endif /* COLORPHASE_H */

