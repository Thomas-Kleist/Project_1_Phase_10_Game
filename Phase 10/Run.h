/* 
 * File:   Run.h
 * Author: Thomas Kleist
 *
 * Created on November 3, 2024, 1:43 PM
 */

#ifndef RUN_H
#define RUN_H

#include "Phase.h"

class Run : public Phase {
public:
    explicit Run(int x) : Phase(x) { }
    virtual ~Run();
    bool addCard(Card);
    void printType() override;
private:

};

#endif /* RUN_H */

