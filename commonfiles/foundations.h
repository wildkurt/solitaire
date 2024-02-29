//
// Created by wendellbest on 1/29/24.
//

#ifndef SOLITAIRE_FOUNDATIONS_H
#define SOLITAIRE_FOUNDATIONS_H

#define MAX_BUFFER 400

#include <stdio.h>
#include "Card.h"

typedef struct Foundations{
    Card foundation[4];
}Foundations;

int getFoundations(Foundations *foundation, int *line, FILE *filelink, char *buffer);
void printFoundations(Foundations *foundation);
void countFoundationCards(Foundations *foundation, Card *countingdeck);
int addCardToFoundations(Foundations *foundation, Card source);
void printFoundationToFile(FILE *outputtofile, Foundations *foundation);

#endif //SOLITAIRE_FOUNDATIONS_H
