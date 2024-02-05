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

void countStockWasteCards(StockWaste *stockwaste, Card *countingdeck){

}