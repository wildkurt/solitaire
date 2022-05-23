//
// Created by wendellbest on 5/20/22.
//

#include "StockWaste.h"

StockWaste::StockWaste(Card *arr) {
    for(int i = 0; i < 30; i++){
        stockWaste[i] = arr[i];
    }
}

void StockWaste::addCard(Card c, int index) {
    stockWaste[index] = c;
}
