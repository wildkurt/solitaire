//
// Created by wendellbest on 1/15/23.
//

#include <iostream>
#include "StockWaste.h"

StockWaste::StockWaste() {
    for(int i = 0; i < 30; i++){
        swarr[i] = Card();
    }
    wasteCardCount = 0;
    stockCardCount = 0;
}

StockWaste::StockWaste(const StockWaste &sw) {
    for(int i = 0; i < 30; i++){
        swarr[i] = sw.swarr[i];
    }
    wasteCardCount = sw.wasteCardCount;
    stockCardCount = sw.stockCardCount;
}

StockWaste &StockWaste::operator=(const StockWaste &sw) {
    for(int i = 0; i < 30; i++){
        swarr[i] = sw.swarr[i];
    }
    wasteCardCount = sw.wasteCardCount;
    stockCardCount = sw.stockCardCount;
    return *this;
}

void StockWaste::addCardToStockWaste(Card card) {
    int i = 0;
    for(;i < 30; i++){
        if(swarr[i].getRank() == 0)
            break;
    }
    swarr[i].setRank(card.getRank());
    swarr[i].setSuit(card.getCardSuit());
}

bool StockWaste::isStockWasteInWinningCondition() {
    if(stockCardCount == 0 && wasteCardCount <= 1)
        return true;
    else
        return false;
}

void StockWaste::printStock() {
    std::cout << "Stock is: ";
    for(int i = 0; swarr[i].getRank() != 0; i++)
        if(reinterpret_cast<const char *>(swarr[i].getRank()) == "|")
            std::cout << swarr[i].getRank() << " ";
        else
            std::cout << swarr[i].getRank() << swarr[i].getCardSuit()<<" ";
}


