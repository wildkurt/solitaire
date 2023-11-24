//
// Created by wendellbest on 11/22/23.
//

#ifndef SOLITAIRE_FOUNDATIONS_H
#define SOLITAIRE_FOUNDATIONS_H

#include <stdio.h>
#include "card.h"

typedef struct Foundation{
    Card fd[4];
}Foundation;

int findFoundation(char *buffer, FILE *input, int *line, Foundation *foundation);
void printFoundation(Foundation *foundation);
Card *fdPtr(Foundation *foundation);
int addCardToFoundation(Card *card, Foundation *foundation);

#endif //SOLITAIRE_FOUNDATIONS_H
