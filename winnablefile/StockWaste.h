//
// Created by wendellbest on 5/20/22.
//

#ifndef SOLITAIRE_STOCKWASTE_H
#define SOLITAIRE_STOCKWASTE_H
#include "cardHeader.h"

class StockWaste {
private:
    Card stockWaste[30];
public:
    StockWaste();
    explicit StockWaste(Card *arr);
    ~StockWaste();
    void addCard(Card c, int index);
};


#endif //SOLITAIRE_STOCKWASTE_H
