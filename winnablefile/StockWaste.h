//
// Created by wendellbest on 1/15/23.
//

#ifndef SOLITAIRE_STOCKWASTE_H
#define SOLITAIRE_STOCKWASTE_H


#include "Card.h"

class StockWaste{
private:
    Card swarr[30];
    int wasteCardCount;
    int stockCardCount;
public:
    StockWaste();
    StockWaste(const StockWaste &sw);
    StockWaste &operator=(const StockWaste &sw);
    ~StockWaste()=default;
    void addCardToStockWaste(Card card);
    void incrementWasteCount(){wasteCardCount++;}
    void incrementStockCount(){stockCardCount++;}
    bool isStockWasteInWinningCondition();

    void printStock();
};


#endif //SOLITAIRE_STOCKWASTE_H
