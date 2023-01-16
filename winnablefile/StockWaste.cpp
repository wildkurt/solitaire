//
// Created by wendellbest on 1/15/23.
//

#include "StockWaste.h"

StockWaste::StockWaste() {
    for(int i = 0; i < 30; i++){
        swarr[i] = Card();
    }
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
    int wasteCount = 0;
    for(int i = 0; i < 30; i++){
        if(swarr[i].isCovered())
            return false;
        if(swarr[i].getRank() != '|' && !swarr[i].isCovered()){
            wasteCount++;
            if(wasteCount > 1)
                return false;
        }
    }
    return true;
}
