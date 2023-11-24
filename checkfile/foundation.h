//
// Created by wende on 5/30/2022.
//
#include "card.h"
#include "check.h"
#include <stdio.h>

#ifndef SOLITAIRE_FOUNDATION_H
#define SOLITAIRE_FOUNDATION_H

typedef struct Foundation{
    Card fd[4];
}Foundation;

int findFoundations(char *buffer, FILE *input, int *line, GameConfiguration *game);
void printFoundation(GameConfiguration *game);
Card *fdPtr(GameConfiguration *game);
int addCardToFoundation(Card *card, GameConfiguration *game);

#endif //SOLITAIRE_FOUNDATION_H
