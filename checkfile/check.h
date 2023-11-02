//
// Created by wende on 5/30/2022.
//
#include "rules.h"
#ifndef SOLITAIRE_CHECK_H
#define SOLITAIRE_CHECK_H

#define MAX_BUFFER 200

void readFile(char *file, Rules *rules);
void countCards(int *covered, int *stock, int *waste);
int missingDuplicateCards();

#endif //SOLITAIRE_CHECK_H
