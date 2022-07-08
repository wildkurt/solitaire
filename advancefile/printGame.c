//
// Created by wendellbest on 6/2/22.
//

#include "printGame.h"
#include "advance.h"
#include "../checkfile/foundation.h"
#include "../checkfile/tableau.h"
#include "../checkfile/stockWaste.h"
#include "printGameToFile.h"

void printGameExchangeFormat(Rules *rules){
    printf("RULES:\n");
    if(rules->turnOver == 3){
        printf(" turn 3\n");
    }
    else{
        printf(" turn 1\n");
    }
    if(rules->limit > 0){
        printf(" limit %d\n", rules->limit);
    }
    else{
        printf(" unlimited\n");
    }
    printf("FOUNDATIONS:\n");
    printFoundation();
    printf("TABLEAUS:\n");
    printTableau();
    printf("STOCK:\n");
    printStockWaste(rules);
    printf("MOVES:\n");
}
void printHumanReadableTableau(Card *ptr){
    if(isRank(ptr->rank) && isSuit(ptr->suit) && ptr->covered == 'F'){
        printf("%c%c ", ptr->rank, ptr->suit);
    }
    else if(isRank(ptr->rank) && isSuit(ptr->suit) && ptr->covered == 'T'){
        printf("## ");
    }
    else if(ptr->rank == '\0'){
        printf(".. ");
    }
}

void printHumanReadable(Rules *rules, int *moves){
    printf("Processed %d moves, all valid\n", *moves);
    printf("Foundations\n");
    printFoundation();
    printf("Tableau\n");
    Card *ptr7 = setPointer(7);
    Card *ptr6 = setPointer(6);
    Card *ptr5 = setPointer(5);
    Card *ptr4 = setPointer(4);
    Card *ptr3 = setPointer(3);
    Card *ptr2 = setPointer(2);
    Card *ptr1 = setPointer(1);
    while(ptr7->rank != '\0' || ptr6->rank != '\0' || ptr5->rank != '\0' || ptr4->rank != '\0' || ptr3->rank != '\0'
    || ptr2->rank != '\0' || ptr1->rank != '\0'){
        if(ptr1->rank == '|')
            ptr1++;
        printHumanReadableTableau(ptr1);
        if(ptr2->rank == '|')
            ptr2++;
        printHumanReadableTableau(ptr2);
        if(ptr3->rank == '|')
            ptr3++;
        printHumanReadableTableau(ptr3);
        if(ptr4->rank == '|')
            ptr4++;
        printHumanReadableTableau(ptr4);
        if(ptr5->rank == '|')
            ptr5++;
        printHumanReadableTableau(ptr5);
        if(ptr6->rank == '|')
            ptr6++;
        printHumanReadableTableau(ptr6);
        if(ptr7->rank == '|')
            ptr7++;
        printHumanReadableTableau(ptr7);
        printf("\n");
        if(ptr1->rank != '\0')
            ptr1++;
        if(ptr2->rank != '\0')
            ptr2++;
        if(ptr3->rank != '\0')
            ptr3++;
        if(ptr4->rank != '\0')
            ptr4++;
        if(ptr5->rank != '\0')
            ptr5++;
        if(ptr6->rank != '\0')
            ptr6++;
        if(ptr7->rank != '\0')
            ptr7++;
    }
    printf("Waste top\n");
    if(stockWasteEmpty())
        printf("(empty)\n");
    else{
        printStockWasteTop(rules);
    }
}

void printGame(Rules *rules, GameConfiguration *gameConfiguration, int *moves){
    if(gameConfiguration->exchangeFormat == 'T'){
        printGameExchangeFormat(rules);
    }
    else{
        printHumanReadable(rules, moves);
    }
    if(gameConfiguration->writeToFile == 'T'){
        printGameToFile(rules, gameConfiguration);
    }
}