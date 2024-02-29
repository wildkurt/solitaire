//
// Created by wendellbest on 1/29/24.
//

#ifndef SOLITAIRE_RULES_H
#define SOLITAIRE_RULES_H

#include <stdio.h>

#define MAX_BUFFER 400

typedef struct Rules{
    //How mantimes can the waste be reset, -1 if unlimited
    int wasteResets;
    //How many card can be turned over from stockpile
    int cardTurnover;
}Rules;

int getRules(Rules *rules, int *pInt, FILE *filelink, char *buffer);
void printRules(Rules *rules);
void printRulesToFile(FILE *outputtofile, Rules *rules);

#endif //SOLITAIRE_RULES_H
