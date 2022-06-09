//
// Created by wendellbest on 6/9/22.
//

#ifndef SOLITAIRE_STOCK_H
#define SOLITAIRE_STOCK_H

#include "Card.h"
#include <string>
#include <fstream>
#include <iostream>

class Stock {
private:
    Card sw[30];
public:
    Stock()=default;
    Stock getStock(std::string inputfilename);
    void printStock();
    void addCardToStock(Card card);
};


#endif //SOLITAIRE_STOCK_H
