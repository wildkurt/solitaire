//
// Created by wendellbest on 6/6/22.
//

#ifndef SOLITAIRE_TABLEAU_H
#define SOLITAIRE_TABLEAU_H


#include <vector>
#include <fstream>
#include "Card.h"

class Tableau {
private:
    std::vector<Card> t7;
    std::vector<Card> t6;
    std::vector<Card> t5;
    std::vector<Card> t4;
    std::vector<Card> t3;
    std::vector<Card> t2;
    std::vector<Card> t1;
public:
    Tableau();
    int getTableau(std::ifstream inputfile);
};


#endif //SOLITAIRE_TABLEAU_H
