//
// Created by wendellbest on 3/19/23.
//

#ifndef SOLITAIRE_TABLEAU_H
#define SOLITAIRE_TABLEAU_H


#include "card.h"
#define TABSIZE 27
class Tableau {
private:
    Card col7[TABSIZE];
    Card col6[TABSIZE];
    Card col5[TABSIZE];
    Card col4[TABSIZE];
    Card col3[TABSIZE];
    Card col2[TABSIZE];
    Card col1[TABSIZE];
public:
    Card * getColPointer(int c);
    void addCardToColumn(int c, Card d);
    void printTableau(std::ofstream *file);
};


#endif //SOLITAIRE_TABLEAU_H
