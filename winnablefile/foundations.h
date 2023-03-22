//
// Created by wendellbest on 3/19/23.
//

#ifndef SOLITAIRE_FOUNDATIONS_H
#define SOLITAIRE_FOUNDATIONS_H


#include "card.h"

class Foundations {
private:
    Card fndtn[4];
public:
    void addCard(int b,Card c);
    void printFoundations(std::ofstream *file);
};


#endif //SOLITAIRE_FOUNDATIONS_H
