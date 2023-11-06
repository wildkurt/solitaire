//
// Created by wende on 5/30/2022.
//
#include <stdio.h>
#include "card.h"
#include "gameconfiguration.h"

#ifndef SOLITAIRE_TABLEAU_H
#define SOLITAIRE_TABLEAU_H

typedef struct Tableau{
    Card t7[30];
    Card t6[30];
    Card t5[30];
    Card t4[30];
    Card t3[30];
    Card t2[30];
    Card t1[30];
}Tableau;

int findTableau(char *buffer, FILE *input, int *line, GameConfiguration *game);
Card *setPointer(int col, Tableau *tableu);
void printTableau(GameConfiguration *game);
Card *getTopColCard(int col, GameConfiguration *game);
int addCardToColumn(Card *ptr, int col, GameConfiguration *game);
void removeCardFromCol(int col, GameConfiguration *game);
int moveColToCol(int src, int dst, GameConfiguration *game);

#endif //SOLITAIRE_TABLEAU_H
