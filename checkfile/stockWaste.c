//
// Created by wendellbest on 5/30/22.
//

#include "stockWaste.h"
#include <string.h>
#include "check.h"

/** Similar to findTableau, but only need to file one array*/
int findStockWaste(char *buffer, FILE *input, int *line, StockWaste *stockwaste){
    char covered = 'F', foundMoves ='F';
    int index = 0;
    do{
        *line = *line + 1;
        if(buffer[0] == '#' || buffer[0] == '\0')
            continue;
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
                stockwaste->sw[index].rank = buffer[i];
                stockwaste->sw[index].suit = 0;
                stockwaste->sw[index].covered = 'F';
                stockwaste->sw[index].stock = 'F';
                covered = 'T';
                index++;
            }
            if(isRank(buffer[i]) && isSuit(buffer[i+1])){
                stockwaste->sw[index].rank = buffer[i];
                stockwaste->sw[index].suit = buffer[i+1];
                if(covered == 'F'){
                    stockwaste->sw[index].covered = 'F';
                    stockwaste->sw[index].stock = 'F';
                }
                else{
                    stockwaste->sw[index].covered = 'T';
                    stockwaste->sw[index].stock = 'T';
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
int doStockWasteCardTurnover(StockWaste *stockwaste, Rules *rules){
    /* Case 1: the stock/waste is empty
     * Case 2: All the cards are in the waste
     * Case 3: Rule turn 3, and less then three
     * cards in the stock
     * Need to move the '|' to separate stock
     * from waste. Waste is on the left, stock
     * on the right.*/
    //No cards in stock/waste
    if(stockwaste->sw[0].rank == '|' && stockwaste->sw[1].rank == '\0'){
        return 0; //false, illegal move
    }
    Card *ptr = stockwaste->sw;
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
        ptr->covered = 'F';
        ptr++;
        count--;
    }
    return 1;
}

int doStockWasteReset(StockWaste *stockwaste, Rules *rules){
    /* Case 1: No cards in stock/waste
     * Case 2: No resets left
     * Case 3: Still stock cards left*/
    int count = 0;
    //No cards left
    if(stockwaste->sw[0].rank == '|' && stockwaste->sw[1].rank == '\0'){
        return 0; //false, illegal move
    }
    //No resets left
    if(rules->limit == 0){
        return 0; //no resets left
    }
    //Still cards in stock
    Card *ptr = stockwaste->sw;
    while(ptr->rank != '|'){
        ptr++;
        count++;
    }
    if((ptr + 1)->rank != '\0'){
        return 0;
    }
    for(int i = count; i > 0 ; i--){
        Card temp = *(ptr -1);
        *(ptr - 1) = *ptr;
        *ptr = temp;
        ptr--;
    }
    if(rules->limit > 0)
        rules->limit = rules->limit - 1;
    return 1;
}
//Just prints the cards in the stock waste.
void printStockWaste(StockWaste *stockwaste){
    Card *ptr = stockwaste->sw;
    while(ptr->rank != '\0'){
        if(ptr->rank == '|')
            printf("%c ", ptr->rank);
        else
            printf("%c%c ", ptr->rank, ptr->suit);
        ptr++;
    }
    printf("\n");
}

int stockWasteEmpty(StockWaste *stockwaste){
    if(stockwaste->sw[0].rank == '|' && stockwaste->sw[1].rank == '\0')
        return 1;
    else
        return 0;
}

void printStockWasteTop(StockWaste *stockwaste, Rules *rules){
    Card *ptr = stockwaste->sw;
    while(ptr->rank != '|'){
        ptr++;
    }
    if(rules->turnOver == 3){
        if((ptr-3)->rank != '\0')
            printf("%c%c ",(ptr-3)->rank, (ptr-3)->suit);
        if((ptr-2)->rank != '\0')
            printf("%c%c ",(ptr-2)->rank, (ptr-2)->suit);
        if((ptr-1)->rank != '\0')
            printf("%c%c ",(ptr-1)->rank, (ptr-1)->suit);
    }
    else{
        if((ptr-1)->rank != '\0')
        printf("%c%c\n", (ptr-1)->rank, (ptr-1)->suit);
    }
}

Card *stockWastePtr(StockWaste *stockwaste){return stockwaste->sw;}

Card *getTopWasteCard(StockWaste *stockwaste){
    Card *ptr = stockwaste->sw;
    while((ptr+1)->rank != '|'){
        ptr++;
    }
    return ptr;
}

void removeWasteCard(Card *ptr){
    /*Removing a card from the waste assuming it is a waste card.
     * Case 1: it is the only card in the stock/waste
     * Case 2: it is the only card in the waste
     * Case 3: there are other cards in the waste*
     * Should only have to remove one card even if draw three is a rule.
     * Assuming the card removal requested is the top card*/
    //Putting card on the heap so it can be copied to array on the stack
    while(ptr->rank != '\0'){
        *ptr = *(ptr+1);
        ptr++;
    }
}