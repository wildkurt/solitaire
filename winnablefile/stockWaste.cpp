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
    numberOfCards += 1;
    if(c.checkIfCardIsCovered())
        numberCovered += 1;
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

bool StockWaste::isSWinWinCond() {
    //need to count cards and see if they are covered
    if(numberCovered == 0 && numberOfCards <= 1)
        return true;
    else
        return false;
}

void StockWaste::getWasteValue(Card *pCard) {
    int index = 0;

    while(true){
        if(sw[index].getRank() == '|' && sw[index + 1].getRank() == '0')
            break;
        else if(sw[(index) + 1].getRank() == '|'){
            pCard[0] = sw[index];
            break;
        }
        index++;
    }
}

void StockWaste::printStockWaste(std::ofstream *ofstream) {

    *ofstream << "STOCK:" << std::endl;
    for(auto & i : sw){
        if(i.getRank() != '0'){
            if(i.getRank() == '|')
                *ofstream << i.getRank() << " ";
            else
                *ofstream << i.getRank() << i.getSuit() << " ";
        }
    }
    *ofstream << std::endl;
}
