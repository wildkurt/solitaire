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

        for(int i = 0; i < MAX_BUFFER && buffer[i] != '#' && buffer[i] != '\n'; i++){
           readBuffer[index++] = buffer[i];
        }
        index = 0;
        if(strstr(readBuffer, "STOCK:") != 0)
            break;
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
        if(index >= 0)
            tabCol--;
        *line +=1;
        memset(buffer,0,MAX_BUFFER);
    }while(fgets(buffer, MAX_BUFFER, input) != 0 && tabCol >= 0);

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
    /* Case 1: The column is empty, just a '|' for rank
     *          a. Card can only have the rank of 'K'
     * Case 2: The column is not empty
     *          a. must check top card in column
     *          b. Card must be one rank lower and opposite color*/
    //get a pointer to the column, then check for empty column or find top card
    Card *tabptr = setPointer(col, tableau);

    //Empty column, can only add K rank
    if(tabptr->rank == '|' && (tabptr + 1)->rank == '\0'){
        tabptr++;
        *tabptr = *ptr;
        return 0;
    }
    //Column not empty, find top card
    while((tabptr + 1)->rank != '\0'){tabptr++;}
    if(isRedOrBlack(tabptr->suit) != isRedOrBlack(ptr->suit)){
        if(rankValue(tabptr->rank) == ptr->rank+1){
            *(++tabptr) = *ptr;
            return 0;
        }
    }
    return 1;
}

int moveColToCol(int src, int dst, Tableau *tableau){
    /* Case 1: the dst col is empty, src must be a King
 * Case 2: The card in src and dst are the top cards
 * Case 3: The card in src has more cards on top of it
 * and all of them need to be moved to other column.*/
    //Get pointers to the columns
    Card *srcptr = setPointer(src, tableau);
    Card *dstptr = setPointer(dst, tableau);
    //increment the destination pointer to top card
    while((dstptr + 1)->rank != 0){dstptr++;}
    //Increment source pointer to first uncovered card
    while(srcptr->rank != '|'){srcptr++;}
    srcptr++;
    //Find a card in source that can be put on destination card
    while(srcptr->rank != 0){
        if((isRedOrBlack(srcptr->suit) != isRedOrBlack(dstptr->suit))&&((rankValue(srcptr->rank) + 1) == rankValue(dstptr->rank)))
            break;
    }
    //if the srcptr is not at end of column, then can add the cards to destination
    if(srcptr->rank != 0){
        //increment destination pointer to next spot
        while(srcptr->rank != 0){
            *(dstptr++) = *(srcptr);
            srcptr->rank = 0;
            srcptr->suit = 0;
            srcptr->covered = 0;
            srcptr->stock = 0;
            srcptr++;
        }
        return 1;
    }
    return 0;
}

void removeCardsFromColumn(Card *ptr){
    Card nullCard = {0,0,0,0};
    while(ptr->rank != 0){
        *ptr = nullCard;
        ptr++;
    }
}