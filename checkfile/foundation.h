//
// Created by wende on 5/30/2022.
//

#ifndef SOLITAIRE_FOUNDATION_H
#define SOLITAIRE_FOUNDATION_H
#include "card.h"

Card fd[4];

int findFoundations(char *buffer, FILE *input, int *line);
void printFoundation();
#endif //SOLITAIRE_FOUNDATION_H
