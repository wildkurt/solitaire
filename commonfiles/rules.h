//
// Created by wendellbest on 11/22/23.
//

#ifndef SOLITAIRE_RULES_H
#define SOLITAIRE_RULES_H

#define MAX_BUFFER 200

#include <stdio.h>

typedef struct Rules{
    int turnOver;
    int limit;
    int line;
    int found;
}Rules;

int findRules(char *buffer, FILE *file, int *line, Rules *rules);
void printRulesSTDOUT(Rules *rules);

#endif //SOLITAIRE_RULES_H
