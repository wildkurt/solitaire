//
// Created by wendellbest on 11/22/23.
//

#ifndef SOLITAIRE_CHECK_H
#define SOLITAIRE_CHECK_H

#include "../commonfiles/gameconfiguration.h"

void readFile(char *inputFile, GameConfiguration *game);
void countCards(int *covered, int *stock, int *waste, GameConfiguration *game);
int missingDuplicateCards(GameConfiguration *game);

#endif //SOLITAIRE_CHECK_H
