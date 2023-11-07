//
// Created by wendellbest on 5/30/22.
//
#include "card.h"
#include "check.h"
#include <stdio.h>

#ifndef SOLITAIRE_STOCKWASTE_H
#define SOLITAIRE_STOCKWASTE_H


typedef struct StockWaste{
    Card sw[30];
}StockWaste;

int findStockWaste(char *buffer, FILE *input, int *line, GameConfiguration *game);
int doStockWasteCardTurnover(GameConfiguration *game);
int doStockWasteReset(GameConfiguration *game);
int stockWasteEmpty(GameConfiguration *game);
void printStockWasteTop(GameConfiguration *game);
void printStockWaste(GameConfiguration *game);
Card *stockWastePtr(GameConfiguration *game);
Card *getTopWasteCard(GameConfiguration *game);
void removeWasteCard(Card *ptr);

#endif //SOLITAIRE_STOCKWASTE_H
