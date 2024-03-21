//
// Created by wendellbest on 1/29/24.
//

#include <string.h>
#include "stockwaste.h"
void initializeStockWaste(StockWaste *stock){
    Card temp = {0,0,0};

    for(int i = 0; i < 26; i++){
        stock->sw[i] = temp;
    }
}
int getStockWaste(StockWaste *stockwaste, int *line, FILE *filelink, char *buffer){
    char cleanBuffer[MAX_BUFFER] = {0};
    int found = 0, index = 0;
    char covered = 't';
    initializeStockWaste(stockwaste);
    while(fgets(buffer, MAX_BUFFER, filelink)){
        (*line)++;
        for(int i = 0; i < MAX_BUFFER && buffer[i] != '#'; i++ ){
            cleanBuffer[i]=buffer[i];
        }
        if(strstr(cleanBuffer,"STOCK:") != 0){
            found++;
        }
        if(strstr(cleanBuffer, "MOVES:" ) != 0){
            if(found == 0)
                return 1;
            else if(found == 1)
                return 2;
            else
                return 0;
        }
        if(found == 1){
            for(int i = 0; cleanBuffer[i] != '\0'; i++){
                if(cleanBuffer[i] == '|'){
                    covered = 'f';
                    found++;
                }
                if(isRank(cleanBuffer[i])&& isSuit(cleanBuffer[i+1])){
                    stockwaste->sw[index].rank = cleanBuffer[i];
                    stockwaste->sw[index].suit = cleanBuffer[i+1];
                    stockwaste->sw[index++].faceUp = covered;
                }
            }
        }
        memset(buffer, 0, MAX_BUFFER);
        memset(cleanBuffer, 0, MAX_BUFFER);
    }
    return 0;
}

void printStockWaste(StockWaste *stockWaste){
    printf("STOCK:\n");
    printf("\t");
    if(stockWaste->sw[0].rank == 0){
        printf("|\n");
    }
    else {
        if(stockWaste->sw[0].faceUp == 'f'){
            printf("| ");
        }
        int i = 0;
        for (; stockWaste->sw[i].rank != 0; i++) {
            if(stockWaste->sw[i-1].faceUp =='t' && stockWaste->sw[i].faceUp == 'f')
                printf("| ");
            printf("%c%c ", stockWaste->sw[i].rank, stockWaste->sw[i].suit);
        }
        if(stockWaste->sw[i-1].faceUp == 't')
            printf("|");
        printf("\n");
    }
}

void countStockWasteCards(StockWaste *stockwaste, Card *countingdeck, int *stock, int *waste){
    for(int i = 0; stockwaste->sw[i].rank != 0; i++) {
        if(stockwaste->sw[i].faceUp == 't')
            (*waste)++;
        else{
            (*stock)++;
        }
        if(stockwaste->sw[i].suit == 'c'){
            countingdeck[isRank(stockwaste->sw[i].rank) - 1] = stockwaste->sw[i];
            countingdeck[isRank(stockwaste->sw[i].rank) - 1].cardCount++;
        }
        else if(stockwaste->sw[i].suit == 'd'){
            countingdeck[isRank(stockwaste->sw[i].rank) + 12] = stockwaste->sw[i];
            countingdeck[isRank(stockwaste->sw[i].rank) + 12].cardCount++;
        }
        else if(stockwaste->sw[i].suit == 'h'){
            countingdeck[isRank(stockwaste->sw[i].rank) + 25] = stockwaste->sw[i];
            countingdeck[isRank(stockwaste->sw[i].rank) + 25].cardCount++;
        }
        else if(stockwaste->sw[i].suit == 's'){
            countingdeck[isRank(stockwaste->sw[i].rank) + 38] = stockwaste->sw[i];
            countingdeck[isRank(stockwaste->sw[i].rank) + 38].cardCount++;
        }
    }
}

void getTopWasteCard(StockWaste *stockwaste, Card *card){
    Card *ptr, *startptr;

    ptr = stockwaste->sw;
    startptr = stockwaste->sw;
    while(ptr->faceUp =='t'){
        ptr++;
    }
    if(ptr->rank == 0 && ptr == startptr)
        return;
    card->rank = (ptr-1)->rank;
    card->suit = (ptr-1)->suit;
    card->faceUp = (ptr-1)->faceUp;
    card->cardCount = (ptr-1)->cardCount;
}

void removeCardFromWaste(StockWaste *stockwaste, Rules *rules, Card *source){
    //Assumed the waste isn't empty when function is called
    //Case: Could be only card left, no stock cards
    //Case: Only one waste card and the rest are stock
    //Need to keep turn over rules in mind
    int i = 0;
    for(; stockwaste->sw[i].rank != 0; i++){
        if(stockwaste->sw[i].rank == source->rank && stockwaste->sw[i].suit == source->suit)
            break;
    }
    if(i == 0 && stockwaste->sw[i+1].rank == 0){
        Card temp = {0,0,0,0,};
        stockwaste->sw[i] = temp;
    }
    else if(i == 0 && stockwaste->sw[i+1].rank != 0 && stockwaste->sw[i+1].faceUp == 'f'){
        for(;stockwaste->sw[i].rank != 0; i++){
            stockwaste->sw[i] = stockwaste->sw[i+1];
            if(i < rules->cardTurnover)
                stockwaste->sw[i].faceUp = 't';
        }
    }
    else{
        for(;stockwaste->sw[i].rank != 0 ;i++){
            stockwaste->sw[i] = stockwaste->sw[i+1];
        }
    }
}

int doStockWasteCardTurnover(StockWaste *stockWaste, Rules *rules){
    Card *swptr = stockWaste->sw;

    while(swptr->faceUp == 't'){swptr++;}
    if(swptr->rank == 0)
        return 1;
    else{
        for(int i = 0; swptr[i].rank != 0 && i < rules->cardTurnover;i++){
            swptr[i].faceUp = 't';
        }
    }
    return 0;
}

int resetWasteToStock(StockWaste *stockwaste){
    //Case 1: Stock/Waste is empty
    //Case 2: Only one waste card, can be flipped whether it makes sense or not
    //Case 3: There are stock cards left
    //Case 4: All the cards are in the waste

    Card *swptr = stockwaste->sw, *startptr = stockwaste->sw;
    if(swptr->rank == 0)
        return 0;
    //Move to the end of the stock pile
    while(swptr->rank != 0){swptr++;}
    swptr--;
    if(swptr->faceUp == 'f')
        return 0;
    do{
        swptr->faceUp = 'f';
    }while(swptr-- != startptr);
    return 1;
}

void printfHumanReadTopWaste(StockWaste *stockwaste){
    for(int i = 0; stockwaste->sw[i].rank != 0; i++){
        if(stockwaste->sw[i].faceUp == 't')
            printf("%c%c ", stockwaste->sw[i].rank, stockwaste->sw[i].suit);
    }
}

void printStockWasteToFile(FILE *outputtofile, StockWaste *stockwaste){
    Card *swptr = stockwaste->sw;
    fprintf(outputtofile,"STOCK:\n");
    fprintf(outputtofile,"\t");
    if(swptr->faceUp == 'f')
        fprintf(outputtofile,"| ");
    while(swptr->rank != 0){
        if((swptr-1)->faceUp == 't' && (swptr)->faceUp == 'f')
            fprintf(outputtofile, "| ");
        fprintf(outputtofile, "%c%c ", swptr->rank, swptr->suit);
        swptr++;
    }
    fprintf(outputtofile,"\n");
}