//
// Created by wende on 5/30/2022.
//


#ifndef SOLITAIRE_FOUNDATION_H
#define SOLITAIRE_FOUNDATION_H
#include "card.h"
#include "check.h"

typedef struct Foundation{
    Card fd[4];
}Foundation;

int findFoundations(char *buffer, FILE *input, int *line, Foundation *foundation);
void printFoundation(Foundation *foundation);
Card *fdPtr(Foundation *foundation);
int addCardToFoundation(Card *card, Foundation *foundation);

#endif //SOLITAIRE_FOUNDATION_H
