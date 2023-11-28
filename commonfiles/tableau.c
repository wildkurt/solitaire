//
// Created by wendellbest on 11/22/23.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tableau.h"

int findTableau(char *buffer, char *readBuffer, FILE *input, int *line, Tableau *tableau){
    Card *ptr;
    int tabCol = 7, index;
    char covered;

    do{
        ptr = setPointer(tabCol, tableau);
        index = 0;
        covered = 'T';
        memset(readBuffer, 0, MAX_BUFFER);

        for(int i = 0; i < MAX_BUFFER; i++){
            if(buffer[i] == '#' || buffer[i] =='\0')
                break;
            else if(isalnum(buffer[i]) || isspace(buffer[i]) || ispunct(buffer[i]))
                readBuffer[index++] = buffer[i];
        }
        index = 0;
        if(strstr(readBuffer,"TABLEAU:")!=0){
            memset(buffer,0,MAX_BUFFER);
            memset(readBuffer, 0, MAX_BUFFER);
            continue;
        }
        for(int i = 0; readBuffer[i] != '\0' && i < MAX_BUFFER; i++){
            /*The following code is for situations where the last line
             * of text is the same as what was found. If using fgets() just
             * results in setting the file to the same line, then just need
             * to break the loop*/

            if(isRank(readBuffer[i]) && isSuit(readBuffer[i+1])){
                ptr[index].rank = readBuffer[i];
                ptr[index].suit = readBuffer[i+1];
                if(covered == 'T'){
                    ptr[index].covered = 'T';
                }
                else{
                    ptr[index].covered ='F';
                }
                ptr[index].stock = 'F';
                index++;
            }
            else if(readBuffer[i] == '|'){
                ptr[index].rank = readBuffer[i];
                ptr[index].suit = 0;
                ptr[index].covered = 'F';
                ptr[index].stock = 'F';
                covered = 'F';
                index++;
            }
        }
        if(index != 0)
            tabCol--;
        if(strstr(readBuffer,"STOCK:")!=0){
            break;
        }
        *line +=1;
        memset(buffer,0,MAX_BUFFER);
    }while(fgets(buffer, MAX_BUFFER, input) != 0 && tabCol != 0);

    if(isTableauCorrect(tableau) && tabCol  == 0){
        return 1;
    }
    else{
        return 0;
    }
}

/** Checks the uncovered cards to make sure they are in
 * descending order and the colors are not the same. The
 * reason I wrote this this way is to reduce duplicate code.
 * The only thing that changes is the tableau array so I just
 * needed to reset the pointer after checking the array*/
int isTableauCorrect(Tableau *tableau){
    Card *ptr;
    int col = 7;
    while(col != 0){
        ptr = setPointer(col, tableau);
        //Move the pointer until reaching '|'
        while(isRank(ptr->rank)){
            ptr++;
        }
        //Increment pointer to card after '|'
        ptr++;
        //Loop checks to see if there is a Card after the pointer
        while(isRank((ptr + 1)->rank)){
            //Check for matching colors
            if(isRedOrBlack(ptr->suit) == isRedOrBlack((ptr + 1)->suit)){
                return 0;
            }
                //Check that the cards are in descending order and only one less
            else if(((rankValue(ptr->rank)) - 1) != rankValue((ptr+1)->rank)){
                return 0;
            }
            ptr++;
        }
        col--;
    }
    return 1;
}

Card *setPointer(int col, Tableau *tableau){
    switch(col){
        case 7 : return tableau->t7;
        case 6 : return tableau->t6;
        case 5 : return tableau->t5;
        case 4 : return tableau->t4;
        case 3 : return tableau->t3;
        case 2 : return tableau->t2;
        case 1 : return tableau->t1;
        default: return 0;
    }
}

void printTableau(Tableau *tableau){
    Card *ptr;
    for(int i = 7; i >= 1; i--){
        ptr = setPointer(i, tableau);
        while(isRank(ptr->rank) || ptr->rank == '|'){
            if(ptr->suit == 0)
                printf("%c ", ptr->rank);
            else
                printf("%c%c ",ptr->rank, ptr->suit);
            ptr++;
        }
        printf("\n");
    }
}

int addCardToColumn(Card *ptr, int col, Tableau *tableau){
    /* Case 1: The column is not empty
     * Case 2: The column is empty*/
    //assuming ptr is on the heap and not the stack
    Card *tabptr = setPointer(col, tableau);
    while(tabptr->rank != '\0'){
        tabptr++;
    }
    if((tabptr - 1)->rank == '|' && ptr->rank != 'K')
        return 0;
    *tabptr = *ptr;
    return 1;
}

void removeCardFromColumn(int col, Tableau *tableau){
    /* Case 1: the top card has other face up cards below it
     * Case 2: the top card has a face down card below it
     * Case 3: the top card is the last card in the col*/
    Card *ptr = setPointer(col, tableau);
    while(ptr->rank != '\0'){
        ptr++;
    }
    ptr--;
    //Card below is covered
    if((ptr-2)->covered == 'T' && (ptr-1)->rank == '|'){
        ptr->rank = '\0';
        ptr->suit = '\0';
        ptr->covered = '\0';
        ptr->stock = '\0';
        Card temp = *(ptr-2);
        *(ptr -2) = *(ptr-1);
        *(ptr-1) = temp;
        (ptr-1)->covered = 'F';
    }
        //Card is the last or card below is face up
    else{
        ptr->rank = '\0';
        ptr->suit = '\0';
        ptr->covered = '\0';
        ptr->stock = '\0';
    }
}

int moveColToCol(int src, int dst, Tableau *tableau){
    /* Case 1: the dst col is empty, src must be a King
 * Case 2: The card in src and dst are the top cards
 * Case 3: The card in src has more cards on top of it
 * and all of them need to be moved to other column.*/
    //Get pointers to the columns
    Card *srcptr = setPointer(src, tableau);
    Card *dstptr = setPointer(dst, tableau);
    //increment the pointers to the '|' then increment by one
    while(srcptr->rank != '|'){
        srcptr++;
    }
    if(srcptr->rank != '\0'){
        srcptr++;
    }
    while(dstptr->rank != '\0'){
        dstptr++;
    }
    dstptr--;
    //src and dst pointers both at a face up card, need to find
    //a card in src that is opposite suit and one rank higher than
    //transfer all cards to dst

    while(srcptr->rank != '\0'){
        if(isRedOrBlack(srcptr->suit) != isRedOrBlack(dstptr->suit) && rankValue(srcptr->rank) == rankValue(dstptr->rank) - 1){
            while(srcptr->rank != '\0'){
                *(++dstptr) = *srcptr;
                srcptr->rank = '\0';
                srcptr->suit = '\0';
                srcptr->covered = '\0';
                srcptr->stock = '\0';
                if((srcptr-1)->rank == '|' && (srcptr-1) != setPointer(src, tableau)){
                    Card temp = *(srcptr-2);
                    *(srcptr-2) = *(srcptr-1);
                    *(srcptr-1) = temp;
                }
                srcptr++;
            }
            return 1;
        }
        else if(dstptr->rank == '|' && srcptr->rank =='K'){
            while(srcptr->rank != '\0'){
                *(++dstptr) = *srcptr;
                srcptr->rank = '\0';
                srcptr->suit = '\0';
                srcptr->covered = '\0';
                srcptr->stock = '\0';
                if((srcptr-1)->rank == '|' && (srcptr-2) != setPointer(src, tableau)){
                    Card temp = *(srcptr-2);
                    *(srcptr-2) = *(srcptr-1);
                    *(srcptr-1) = temp;
                }
                srcptr++;
            }
            return 1;
        }
        srcptr++;
    }
    return 0;
}