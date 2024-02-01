//
// Created by wendellbest on 1/29/24.
//

#ifndef SOLITAIRE_FOUNDATIONS_H
#define SOLITAIRE_FOUNDATIONS_H

#include <stdio.h>
#include "Card.h"

#define MAX_BUFFER 200

typedef struct Foundations{
    Card foundation[4];
}Foundations;

int getFoundations(Foundations *foundation, int *line, FILE *filelink, char *buffer);
void printFoundations(Foundations *foundation);

#endif //SOLITAIRE_FOUNDATIONS_H
