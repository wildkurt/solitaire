//
// Created by wendellbest on 1/29/24.
//

#ifndef SOLITAIRE_TABLEAU_H
#define SOLITAIRE_TABLEAU_H

#include <stdio.h>
#include "Card.h"

#define MAX_BUFFER 400

typedef struct Tableau{
    Card tab1[22];
    Card tab2[22];
    Card tab3[22];
    Card tab4[22];
    Card tab5[22];
    Card tab6[22];
    Card tab7[22];
}Tableau;

int getTableau(Tableau *tableau, int *line, FILE *filelink, char *buffer);
Card *getPointerToColumn(int column, Tableau *tableau);
int checkIfColumnCorrect(Card *column);
int redAndBlack(char suit1, char suit2);
void printTableau(Tableau *tableau);
void countTableauCards(Tableau *tableau, Card *countingdeck);
void getTopTableauColumnCard(Tableau *tableau, char to, Card *destination);
void addCardToTableauColumn(Tableau *tableau, char to, Card *source);
int moveCardFromColumnToColumn(Tableau  *tableau, char from, char to);
void removeCardFromColumn(Tableau *tableau, char column, Card source);

#endif //SOLITAIRE_TABLEAU_H
