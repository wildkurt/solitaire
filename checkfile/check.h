//
// Created by wendellbest on 1/29/24.
//

#ifndef SOLITAIRE_CHECK_H
#define SOLITAIRE_CHECK_H

#include "../commonfiles/gameconfiguration.h"

int getGameFile(GameConfiguration *game, char *filename);
int countCards(GameConfiguration *game, int *covered, int *stock, int *waste);

#endif //SOLITAIRE_CHECK_H
