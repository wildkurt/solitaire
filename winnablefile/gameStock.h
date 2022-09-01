//
// Created by wendellbest on 7/7/22.
//

#ifndef SOLITAIRE_GAMESTOCK_H
#define SOLITAIRE_GAMESTOCK_H


#include <string>
#include <vector>
#include "card.h"

class gameStock {
private:
    std::string filename;
    std::vector <card> sw;
public:
    void getStock(std::__cxx11::basic_string<char> basicString);

    void printStock();
};


#endif //SOLITAIRE_GAMESTOCK_H
