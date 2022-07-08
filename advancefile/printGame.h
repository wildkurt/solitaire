//
// Created by wendellbest on 6/2/22.
//



#ifndef SOLITAIRE_PRINTGAME_H
#define SOLITAIRE_PRINTGAME_H

#include "advance.h"
#include "../checkfile/check.h"

void printGame(Rules *rules, GameConfiguration *gameConfiguration, int *moves);
void printHumanReadable(Rules *rules, int *moves);
void printGameExchangeFormat(Rules *rules);

#endif //SOLITAIRE_PRINTGAME_H
