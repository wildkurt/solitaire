//
// Created by wende on 5/30/2022.
//

#include "tableau.h"
#include <string.h>

void setPointer(Card *ptr, int col){
    switch(col){
        case 7 : ptr = t7; break;
        case 6 : ptr = t6; break;
        case 5 : ptr = t5; break;
        case 4 : ptr = t4; break;
        case 3 : ptr = t3; break;
        case 2 : ptr = t2; break;
        case 1 : ptr = t1; break;
        default: ptr = 0; break;
    }
}

int isTableauCorrect(){
    Card *ptr;

    for(int i = 7; i >=1; i--){
        setPointer(ptr,i);
        while(ptr->rank != '|'){
            ptr++;
        }
        ptr++;
        while(isRank(ptr->rank)){
            if(isRedOrBlack(ptr->suit) == isRedOrBlack((ptr+1)->suit))
                return 0;
            ptr++;
        }
    }
    return 1;
}

int findTableau(char *buffer, FILE *input, int *line){
    Card *ptr;
    int tabCol = 7, index;
    char covered = 'T';

    do{
        line++;
        setPointer(ptr, tabCol);
        index = 0;
        for(int i = 0; buffer[i] != '\n'; i++){
            if(strstr(buffer,"TABLEAU:")!=0){
                fgets(buffer, 50, input);
                continue;
            }
            if(isRank(buffer[i]) && isSuit(buffer[i+1])){
                ptr[index].rank = buffer[i];
                ptr[index].suit = buffer[i+1];
                if(covered == 'T'){
                    ptr[index].covered = 'T';
                }
                else{
                    ptr[index].covered ='F';
                }
                index++;
            }
            else if(buffer[i] == '|'){
                ptr[index].rank = buffer[i];
                ptr[index].suit = 0;
                ptr[index].covered = 'F';
                index++;
            }
        }
        if(strstr(buffer,"TABLEAU:")==0)
            tabCol--;
    }while(fgets(buffer, 50, input) != 0 && tabCol != 0);
    if(isTableauCorrect() && tabCol == 0){
        return 1;
    }
    else{
        return 0;
    }
}

void printTableau(){
    Card *ptr;
    for(int i = 7; i >= 1; i--){
        setPointer(ptr,i);
        while(isRank(ptr->rank)){
            printf("%c%c ",ptr->rank, ptr->suit);
            ptr++;
        }
    }
}