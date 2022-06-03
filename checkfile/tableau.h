//
// Created by wende on 5/30/2022.
//

#ifndef SOLITAIRE_TABLEAU_H
#define SOLITAIRE_TABLEAU_H

#include <stdio.h>
#include "card.h"

int findTableau(char *buffer, FILE *input, int *line);
Card *setPointer( int col);
void printTableau();
Card *getTopColCard(int col);
void addCardToColumn(Card *ptr, int col);

#endif //SOLITAIRE_TABLEAU_H
