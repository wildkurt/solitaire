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
    int numberCovered;
    int numberOfCards;
public:
    void addCardToSW(Card c);
    void printStockWaste();
    bool isSWinWinCond();

    void getWasteValue(Card pCard[8]);
};


#endif //SOLITAIRE_STOCKWASTE_H
