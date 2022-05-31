//
// Created by wendellbest on 5/30/22.
//

#include "stockWaste.h"
#include <string.h>

int findStockWaste(char *buffer, FILE *input, int *line){
    char covered = 'F', foundMoves ='F';
    int index = 0;
    do{
        for(int i = 0; buffer[i] != '\n'; i++){
            if(buffer[i] =='#')
                break;
            if(strstr(buffer, "STOCK:") != 0){
                fgets(buffer, 50, input);
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
                covered = 'T';
                index++;
            }
            if(isRank(buffer[i]) && isSuit(buffer[i+1])){
                sw[index].rank = buffer[i];
                sw[index].suit = buffer[i+1];
                if(covered == 'F')
                    sw[index].covered = 'F';
                else
                    sw[index].covered = 'T';
                index++;
            }
        }
    }while(fgets(buffer, 50, input)!=0 && foundMoves == 'F');
    return 1;
}

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