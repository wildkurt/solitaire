//
// Created by wendellbest on 11/22/23.
//

#ifndef SOLITAIRE_TABLEAU_H
#define SOLITAIRE_TABLEAU_H

#include <bits/types/FILE.h>
#include "card.h"

typedef struct Tableau{
    Card t7[30];
    Card t6[30];
    Card t5[30];
    Card t4[30];
    Card t3[30];
    Card t2[30];
    Card t1[30];
}Tableau;

int findTableau(char *buffer, FILE *input, int *line, Tableau *tableu);
Card *setPointer(int col, Tableau *tableau);
void printTableau(Tableau *tableau);
int addCardToColumn(Card *ptr, int col, Tableau *tableau);
void removeCardFromColumn(int col, Tableau *tableau);
int moveColToCol(int src, int dst, Tableau *tableau);
int isTableauCorrect(Tableau *tableau);

#endif //SOLITAIRE_TABLEAU_H
