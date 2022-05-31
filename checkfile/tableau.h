//
// Created by wende on 5/30/2022.
//

#ifndef SOLITAIRE_TABLEAU_H
#define SOLITAIRE_TABLEAU_H

#include <stdio.h>
#include "card.h"

Card t7[30];
Card t6[30];
Card t5[30];
Card t4[30];
Card t3[30];
Card t2[30];
Card t1[30];

int findTableau(char *buffer, FILE *input, int *line);
Card *setPointer( int col);
int countCoveredCards();
void printTableau();

#endif //SOLITAIRE_TABLEAU_H
