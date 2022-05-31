//
// Created by wendellbest on 5/30/22.
//
#include "check.h"
#include "card.h"
#include "stockWaste.h"
#include "tableau.h"

void countCards(int *covered, int *stock, int *waste){
    int countCover = 0, countStock = 0, countWaste = 0, column = 7;
    char stockC = 'F', tabC = 'T';
    Card *ptr;

    for(int i = 0; isRank(sw[i].rank) || sw[i].rank == '|'; i++){
        if(sw[i].covered == 'T')
            countCover++;
        if(sw[i].rank == '|')
            stockC = 'T';
        if(stockC == 'F' && isRank(sw[i].rank))
            countWaste++;
        else if(isRank(sw[i].rank))
            countStock++;
    }
    countCover = countCover + countCoveredCards();
    *covered = countCover;
    *stock = countStock;
    *waste = countWaste;
}