//
// Created by wende on 5/30/2022.
//
#ifndef SOLITAIRE_CHECK_H
#define SOLITAIRE_CHECK_H

#include "gameconfiguration.h"

void readFile(char *file, GameConfiguration *game);
void countCards(int *covered, int *stock, int *waste, GameConfiguration *game);
int missingDuplicateCards(GameConfiguration *game);

#endif //SOLITAIRE_CHECK_H
