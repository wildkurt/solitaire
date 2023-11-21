//
// Created by wende on 5/30/2022.
//

#ifndef SOLITAIRE_TABLEAU_H
#define SOLITAIRE_TABLEAU_H

#include "card.h"
#include "gameconfiguration.h"

typedef struct Tableau{
    Card t7[30];
    Card t6[30];
    Card t5[30];
    Card t4[30];
    Card t3[30];
    Card t2[30];
    Card t1[30];
}Tableau;

int findTableau(char *buffer, FILE *input, int *line, Tableau *tableau);
Card *setPointer(int col, Tableau *tableu);
void printTableau(Tableau *tableau);
Card *getTopColCard(int col, Tableau *tableau);
int addCardToColumn(Card *ptr, int col, Tableau *tableau);
void removeCardFromCol(int col, Tableau *tableau);
int moveColToCol(int src, int dst, Tableau *tableau);

#endif //SOLITAIRE_TABLEAU_H
