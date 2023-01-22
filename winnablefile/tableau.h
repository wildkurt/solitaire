//
// Created by wendellbest on 1/15/23.
//

#ifndef SOLITAIRE_TABLEAU_H
#define SOLITAIRE_TABLEAU_H
#include "Card.h"
/**The object for a tableau*/
class Tableau{
private:
    Card col1[27];
    Card col2[27];
    Card col3[27];
    Card col4[27];
    Card col5[27];
    Card col6[27];
    Card col7[27];
    Card *colptr(int col);
public:
    Tableau();
    void addCardToTab(int col, Card card);
    bool areColumnCardsCovered();

    void printTableaus();
};


#endif //SOLITAIRE_TABLEAU_H
