//
// Created by wendellbest on 11/1/23.
//

#ifndef SOLITAIRE_RULES_H
#define SOLITAIRE_RULES_H

#include "gameconfiguration.h"

typedef struct Rules{
    int turnOver; // how many cards can be turned over in stock at a time
    int limit; // How many times the stock/waste can be reset
    int line;
    int found;
}Rules;

int findRules(char *buffer, FILE *file, int *line, Rules *rules);
void printRulesSTDOUT(Rules rules);

#endif //SOLITAIRE_RULES_H
