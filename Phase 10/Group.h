/*
 * File:   Group.h
 * Author: Thomas Kleist
 *
 * Created on November 3, 2024, 9:56 AM
 */

#ifndef GROUP_H
#define GROUP_H

#include "Phase.h"

class Group : public Phase {
public:
    explicit Group(int x) : Phase(x) { }
    virtual ~Group();
    bool addCard(Card);
    void printType();
private:

};

#endif /* GROUP_H */

