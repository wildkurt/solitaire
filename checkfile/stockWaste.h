//
// Created by wendellbest on 5/30/22.
//

#ifndef SOLITAIRE_STOCKWASTE_H
#define SOLITAIRE_STOCKWASTE_H

#include "card.h"
#include <stdio.h>

Card sw[30];

int findStockWaste(char *buffer, FILE *input, int *line);
void printStockWaste();

#endif //SOLITAIRE_STOCKWASTE_H
