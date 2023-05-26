//
// Created by wendellbest on 3/19/23.
//

#include <iostream>
#include <fstream>
#include "stockWaste.h"

void StockWaste::addCardToSW(Card c) {
    Card *ptr = sw;
    while((ptr)->getRank() != '0'){ptr++;}
    *ptr=c;
}

void StockWaste::printStockWaste() {
    std::cout << "STOCK:" << std::endl;
    for(int i = 0; i < SWSIZE; i++){
        if(sw[i].getRank() != '0'){
            if(sw[i].getRank() == '|')
                std::cout << sw[i].getRank() << " ";
            else
                std::cout << sw[i].getRank() << sw[i].getSuit() << " ";
        }
    }
    std::cout << std::endl;
}
