//
// Created by wendellbest on 5/30/22.
//

#ifndef SOLITAIRE_STOCKWASTE_H
#define SOLITAIRE_STOCKWASTE_H

#include "card.h"
#include "check.h"
#include <stdio.h>

int findStockWaste(char *buffer, FILE *input, int *line);
int doStockWasteCardTurnover(Rules *rules);
int doStockWasteReset(Rules *rules);
int stockWasteEmpty();
void printStockWasteTop(Rules *rules);
void printStockWaste();
Card *stockWastePtr();
Card *getTopWasteCard();
Card *removeWasteCard(Card *ptr);

#endif //SOLITAIRE_STOCKWASTE_H
