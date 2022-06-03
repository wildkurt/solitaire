//
// Created by wende on 5/30/2022.
//

#ifndef SOLITAIRE_FOUNDATION_H
#define SOLITAIRE_FOUNDATION_H
#include "card.h"
#include <stdio.h>

int findFoundations(char *buffer, FILE *input, int *line);
void printFoundation();
Card *fdPtr();
int addCardToFoundation(Card *card);
#endif //SOLITAIRE_FOUNDATION_H
