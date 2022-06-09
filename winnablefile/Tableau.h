//
// Created by wende on 6/7/2022.
//

#ifndef SOLITAIRE_TABLEAU_H
#define SOLITAIRE_TABLEAU_H

#include "Card.h"
#include <string>

class Tableau {
private:
    Card t7[30];
    Card t6[30];
    Card t5[30];
    Card t4[30];
    Card t3[30];
    Card t2[30];
    Card t1[30];
public:
    Tableau()=default;
    Tableau getTableau(std::string inputfilename);
    void addCardToCol(Card card, int col);
    Card *getColPtr(int c);
    void printTableau();
};


#endif //SOLITAIRE_TABLEAU_H
