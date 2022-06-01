//
// Created by wendellbest on 5/30/22.
//

#include "stockWaste.h"
#include <string.h>
#include "check.h"
/** Similar to findTableau, but only need to file one array*/
int findStockWaste(char *buffer, FILE *input, int *line){
    char covered = 'F', foundMoves ='F';
    int index = 0;
    do{
        for(int i = 0; buffer[i] != '\n' && i < MAX_BUFFER; i++){
            if(buffer[i] =='#')
                break;
            if(strstr(buffer, "STOCK:") != 0){
                fgets(buffer, MAX_BUFFER, input);
                if(strstr(buffer, "MOVES") != 0)
                    foundMoves = 'T';
                if(strstr(buffer, "STOCK:") != 0)
                    break;
                i--;
                continue;
            }
            if(strstr(buffer, "MOVES:") != 0){
                fputs(buffer,input);
                foundMoves = 'T';
                break;
            }
            if(buffer[i] == '|'){
                sw[index].rank = buffer[i];
                sw[index].suit = 0;
                sw[index].covered = 'F';
                sw[index].stock = 'F';
                covered = 'T';
                index++;
            }
            if(isRank(buffer[i]) && isSuit(buffer[i+1])){
                sw[index].rank = buffer[i];
                sw[index].suit = buffer[i+1];
                if(covered == 'F'){
                    sw[index].covered = 'F';
                    sw[index].stock = 'F';
                }
                else{
                    sw[index].covered = 'T';
                    sw[index].stock = 'T';
                }
                index++;
            }
        }
        if(foundMoves == 'T')
            break;
        memset(buffer, 0, MAX_BUFFER);
    }while(fgets(buffer, MAX_BUFFER, input)!=0);
    return 1;
}
int doStockWasteCardTurnover(Rules *rules){
    /* Case 1: the stock/waste is empty
     * Case 2: All the cards are in the waste
     * Case 3: Rule turn 3, and less then three
     * cards in the stock
     * Need to move the '|' to separate stock
     * from waste. Waste is on the left, stock
     * on the right.*/
    //No cards in stock/waste
    if(sw[0].rank == '|' && sw[1].rank == '\0'){
        return 0; //false, illegal move
    }
    Card *ptr = sw;
    while(ptr->rank != '|'){
        ptr++;
    }
    //No more stock cards
    if((ptr+1)->rank == '\0'){
        return 0;
    }
    //Turn over one or three cards
    int count = rules->turnOver;
    while(count > 0 && ptr->rank != '\0'){
        Card temp = *ptr;
        *ptr = *(ptr + 1);
        *(ptr + 1) = temp;
        ptr++;
        count--;
    }
    return 1;
}

int doStockWasteReset(Rules *rules){
    /* Case 1: No cards in stock/waste
     * Case 2: No resets left
     * Case 3: Still stock cards left*/
    //No cards left
    if(sw[0].rank == '|' && sw[1].rank == '\0'){
        return 0; //false, illegal move
    }
    //No resets left
    if(rules->limit == 0){
        return 0; //no resets left
    }
    //Still cards in stock
    //TODO

    //TODO perform stock waste reset
}
//Just prints the cards in the stock waste.
void printStockWaste(){
    Card *ptr = sw;
    while(isRank(ptr->rank) || ptr->rank =='|'){
        if(ptr->suit == 0)
            printf("%c %c ",ptr->rank, ptr->covered);
        else
            printf("%c%c %c ", ptr->rank, ptr->suit, ptr->covered);
        ptr++;
    }
    printf("\n");
}