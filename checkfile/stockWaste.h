//
// Created by wendellbest on 5/30/22.
//


#ifndef SOLITAIRE_STOCKWASTE_H
#define SOLITAIRE_STOCKWASTE_H

#include "card.h"
#include "check.h"
#include <stdio.h>

typedef struct StockWaste{
    Card sw[30];
}StockWaste;

int findStockWaste(char *buffer, FILE *input, int *line, StockWaste *stockwaste);
int doStockWasteCardTurnover(StockWaste *stockwaste, Rules *rules);
int doStockWasteReset(StockWaste *stockwaste, Rules *rules);
int stockWasteEmpty(StockWaste *stockwaste);
void printStockWasteTop(StockWaste *stockwaste, Rules *rules);
void printStockWaste(StockWaste *stockwaste);
Card *stockWastePtr(StockWaste *stockwaste);
Card *getTopWasteCard(StockWaste *stockwaste);
void removeWasteCard(Card *ptr);

#endif //SOLITAIRE_STOCKWASTE_H
