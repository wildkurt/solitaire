//
// Created by wendellbest on 1/15/23.
//

#ifndef SOLITAIRE_FOUNDATION_H
#define SOLITAIRE_FOUNDATION_H
#include "Card.h"
/**The object for a Foundation*/
class Foundation{
private:
    //c, d, h, s
    Card farr[4];
public:
    Foundation();
    Foundation(const Foundation & fndtn);
    Foundation &operator=(const Foundation & fndtn);
    ~Foundation()=default;
    bool isSafeToMoveCard(Card card);
    void addCardToFoundation(Card card);
    void printFoundations();
};


#endif //SOLITAIRE_FOUNDATION_H
