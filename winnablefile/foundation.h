//
// Created by wendellbest on 1/15/23.
//

#ifndef SOLITAIRE_FOUNDATION_H
#define SOLITAIRE_FOUNDATION_H
#include "Card.h"
/**The object for a Foundation*/
class Foundation{
private:
    Card farr[4];
public:
    Foundation();
    bool isSafeToMoveCard(Card card);
    void addCardToFoundation(Card card);
};


#endif //SOLITAIRE_FOUNDATION_H
