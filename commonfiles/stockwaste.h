//
// Created by wendellbest on 1/29/24.
//

#ifndef SOLITAIRE_STOCKWASTE_H
#define SOLITAIRE_STOCKWASTE_H

#include <stdio.h>
#include "Card.h"
#include "rules.h"

#define MAX_BUFFER 400

typedef struct StockWaste{
    Card sw[26];
}StockWaste;

int getStockWaste(StockWaste *stockwaste, int *line, FILE *filelink, char *buffer);
void printStockWaste(StockWaste *stockWaste);
void countStockWasteCards(StockWaste *stockwaste, Card *countingdeck, int *stock, int *waste);
void getTopWasteCard(StockWaste *stockwaste, Card *card);
void removeCardFromWaste(StockWaste *stockwatse, Rules *rules, Card *source);
int doStockWasteCardTurnover(StockWaste *stockWaste, Rules *rules);
int resetWasteToStock(StockWaste *stockwaste);
void printfHumanReadTopWaste(StockWaste *stockwaste);
void printStockWasteToFile(FILE *outputtofile, StockWaste *stockwaste);

#endif //SOLITAIRE_STOCKWASTE_H
