//
// Created by wende on 5/30/2022.
//

#ifndef SOLITAIRE_CHECK_H
#define SOLITAIRE_CHECK_H

#define MAX_BUFFER 200

typedef struct{
    int turnOver; // how many cards can be turned over in stock at a time
    int limit; // How many times the stock/waste can be reset
}Rules;

void countCards(int *covered, int *stock, int *waste);
int missingDuplicateCards();

#endif //SOLITAIRE_CHECK_H
