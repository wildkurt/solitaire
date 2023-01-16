//
// Created by wendellbest on 1/15/23.
//

#ifndef SOLITAIRE_STOCKWASTE_H
#define SOLITAIRE_STOCKWASTE_H


#include "Card.h"

class StockWaste{
private:
    Card swarr[30];
public:
    StockWaste();
    void addCardToStockWaste(Card card);
    bool isStockWasteInWinningCondition();
};


#endif //SOLITAIRE_STOCKWASTE_H
