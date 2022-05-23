//
// Created by wendellbest on 5/19/22.
//

#ifndef SOLITAIRE_FOUNDATIONS_H
#define SOLITAIRE_FOUNDATIONS_H
#include <vector>
#include "cardHeader.h"

class foundations {
private:
    Card foundation [4];
public:
    foundations()= default;
    ~foundations()= default;
    Card getFoundation(int index){return foundation[index];}
    bool isFoundationFull();
    bool addCardToFoundation(Card n);
};

#endif //SOLITAIRE_FOUNDATIONS_H
