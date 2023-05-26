//
// Created by wendellbest on 3/19/23.
//

#ifndef SOLITAIRE_STOCKWASTE_H
#define SOLITAIRE_STOCKWASTE_H


#include "card.h"
#define SWSIZE 27
class StockWaste {
private:
    Card sw[SWSIZE];
public:
    void addCardToSW(Card c);
    void printStockWaste();
};


#endif //SOLITAIRE_STOCKWASTE_H
