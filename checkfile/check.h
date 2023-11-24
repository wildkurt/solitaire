//
// Created by wende on 5/30/2022.
//

#include "gameconfiguration.h"

#ifndef SOLITAIRE_CHECK_H

#define MAX_BUFFER 200


void readFile(char *file, GameConfiguration *game);
void countCards(int *covered, int *stock, int *waste, GameConfiguration *game);
int missingDuplicateCards(GameConfiguration *game);

#endif //SOLITAIRE_CHECK_H
