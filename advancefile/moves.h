//
// Created by wendellbest on 5/31/22.
//

#ifndef SOLITAIRE_MOVES_H
#define SOLITAIRE_MOVES_H
#include <stdio.h>
#include "../checkfile/check.h"
#include "advance.h"

int moves(FILE *input, int *line, int *moves, Rules *rules, GameConfiguration *gameconfiguration);

#endif //SOLITAIRE_MOVES_H
