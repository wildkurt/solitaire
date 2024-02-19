//
// Created by wendellbest on 1/29/24.
//

#include <string.h>
#include "stockwaste.h"

int getStockWaste(StockWaste *stockwaste, int *line, FILE *filelink, char *buffer){
    char cleanBuffer[MAX_BUFFER] = {0};
    int found = 0, index = 0;
    char covered = 't';

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
    if(stockWaste->sw[0].rank == 0){
        printf("|\n");
    }
    else {
        if(stockWaste->sw[0].faceUp == 'f'){
            printf("| ");
        }
        for (int i = 0; stockWaste->sw[i].rank != 0; i++) {
            if(stockWaste->sw[i-1].faceUp =='t' && stockWaste->sw[i].faceUp == 'f')
                printf("| ");
            printf("%c%c ", stockWaste->sw[i].rank, stockWaste->sw[i].suit);
        }
        printf("\n");
    }
}

void countStockWasteCards(StockWaste *stockwaste, Card *countingdeck, int *stock, int *waste){
    for(int i = 0; stockwaste->sw[i].rank != 0; i++){
        if(stockwaste->sw[i].faceUp =='t'){
            (*waste)++;
        }
        else{
            (*stock)++;
        }
        if(stockwaste->sw[i].suit == 'c'){
            countingdeck[isRank(stockwaste->sw[i].rank) - 1].rank = stockwaste->sw[i].rank;
            countingdeck[isRank(stockwaste->sw[i].rank) - 1].suit = stockwaste->sw[i].suit;
            countingdeck[isRank(stockwaste->sw[i].rank) - 1].faceUp = stockwaste->sw[i].faceUp;
            countingdeck[isRank(stockwaste->sw[i].rank) - 1].cardCount++;
        }
        if(stockwaste->sw[i].suit == 'd'){
            countingdeck[13 + isRank(stockwaste->sw[i].rank) - 1].rank = stockwaste->sw[i].rank;
            countingdeck[13 + isRank(stockwaste->sw[i].rank) - 1].suit = stockwaste->sw[i].suit;
            countingdeck[13 + isRank(stockwaste->sw[i].rank) - 1].faceUp = stockwaste->sw[i].faceUp;
            countingdeck[13 + isRank(stockwaste->sw[i].rank) - 1].cardCount++;
        }
        if(stockwaste->sw[i].suit == 'h'){
            countingdeck[26 + isRank(stockwaste->sw[i].rank) - 1].rank = stockwaste->sw[i].rank;
            countingdeck[26 + isRank(stockwaste->sw[i].rank) - 1].suit = stockwaste->sw[i].suit;
            countingdeck[26 + isRank(stockwaste->sw[i].rank) - 1].faceUp = stockwaste->sw[i].faceUp;
            countingdeck[26 + isRank(stockwaste->sw[i].rank) - 1].cardCount++;
        }
        if(stockwaste->sw[i].suit == 's'){
            countingdeck[39 + isRank(stockwaste->sw[i].rank) - 1].rank = stockwaste->sw[i].rank;
            countingdeck[39 + isRank(stockwaste->sw[i].rank) - 1].suit = stockwaste->sw[i].suit;
            countingdeck[39 + isRank(stockwaste->sw[i].rank) - 1].faceUp = stockwaste->sw[i].faceUp;
            countingdeck[39 + isRank(stockwaste->sw[i].rank) - 1].cardCount++;
        }
    }
}

void getTopWasteCard(StockWaste *stockwaste, Card *card){
    Card *ptr;

    ptr = stockwaste->sw;

    while(ptr->faceUp =='t'){
        ptr++;
    }
    if(ptr->rank == 0)
        return;
    card->rank = (ptr-1)->rank;
    card->suit = (ptr-1)->suit;
    card->faceUp = (ptr-1)->faceUp;
    card->cardCount = (ptr+1)->cardCount;
}

void removeCardFromWaste(StockWaste *stockwaste, Rules *rules, Card *source){
    //Assumed the waste isn't empty when function is called
    //Case: Could be only card left, no stock cards
    //Case: Only one waste card and the rest are stock
    //Need to keep turn over rules in mind

    Card *ptr = stockwaste->sw;

    while(1){
        if(ptr->rank == source->rank && ptr->suit == source->suit)
            break;
        ptr++;
    }
    //Only card in deck
    if((ptr + 1)->rank == 0){
        ptr->rank = 0;
        ptr->suit = 0;
        ptr->faceUp = 0;
        ptr->cardCount = 0;
    }
    //Top waste card, but there is stock
    if((ptr+1)->rank != 0){
        //Only one waste card
        if(ptr - 1 == NULL){
            while(ptr->rank != 0){
                *ptr = *(ptr + 1);
                ptr++;
            }
            for(int i = 0; i < rules->cardTurnover; i++){
                stockwaste->sw[i].faceUp = 't';
            }
        }
        else{
            while(ptr->rank != 0){
                *ptr=*(ptr+1);
                ptr++;
            }
        }
    }
}