//
// Created by wende on 5/30/2022.
//

#ifndef SOLITAIRE_CHECK_H
#define SOLITAIRE_CHECK_H

#define MAX_BUFFER 100

typedef struct{
    int turnOver;
    int limit;
}Rules;

void countCards(int *covered, int *stock, int *waste);
int missingDuplicateCards();

#endif //SOLITAIRE_CHECK_H
