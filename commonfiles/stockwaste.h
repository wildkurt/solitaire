//
// Created by wendellbest on 11/22/23.
//

#ifndef SOLITAIRE_STOCKWASTE_H
#define SOLITAIRE_STOCKWASTE_H

#include "card.h"
#include "rules.h"

typedef struct StockWaste{
    Card sw[60];
}StockWaste;

int findStockWaste(char *buffer, char *readBuffer, FILE *input, int *line, StockWaste *stockWaste);
int doStockWasteCardTurnover(Rules *rules, StockWaste *stockWaste);
int doStockWasteReset(StockWaste *stockWaste, Rules *rules);
int stockWasteEmpty(StockWaste *stockWaste);
void printStockWasteTop(StockWaste *stockWaste, Rules *rules);
void printStockWaste(StockWaste *stockWaste);
Card *stockWastePtr(StockWaste *stockWaste);
Card *getTopWasteCard(StockWaste *stockWaste);
void removeWasteCard(Card *ptr);

#endif //SOLITAIRE_STOCKWASTE_H
