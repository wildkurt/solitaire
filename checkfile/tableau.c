//
// Created by wende on 5/30/2022.
//

#include "tableau.h"
#include <string.h>
#include "check.h"
#include <stdlib.h>

/** This has all the functions that operate on tableau and
 * holds the tableaus themselves.*/
Card t7[30];
Card t6[30];
Card t5[30];
Card t4[30];
Card t3[30];
Card t2[30];
Card t1[30];

/** Allows a function to get a pointer from the desired tableau*/
Card *setPointer( int col){
    switch(col){
        case 7 : return t7;
        case 6 : return t6;
        case 5 : return t5;
        case 4 : return t4;
        case 3 : return t3;
        case 2 : return t2;
        case 1 : return t1;
        default: return 0;
    }
}

/** Checks the uncovered cards to make sure they are in
 * descending order and the colors are not the same. The
 * reason I wrote this this way is to reduce duplicate code.
 * The only thing that changes is the tableau array so I just
 * needed to reset the pointer after checking the array*/
int isTableauCorrect(){
    Card *ptr;
    int col = 7;
    while(col != 0){
        ptr = setPointer(col);
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
/** Finds the tableau columns. It is assume that the Tableaus are
 * always on their own lines. Using memset to clear the buffer to
 * keep anything extra from being in the buffer. This also sets
 * the cards to covered if they are before the '|'. When all of
 * the columsn are found, the columsn are checked for correctness.*/
int findTableau(char *buffer, FILE *input, int *line){
    Card *ptr;
    int tabCol = 7, index;
    char covered;

    do{
        *line +=1;
        ptr = setPointer(tabCol);
        index = 0;
        covered = 'T';
        if(strstr(buffer,"TABLEAU:")!=0)
            fgets(buffer, MAX_BUFFER, input);
        for(int i = 0; buffer[i] != '\n' && i < MAX_BUFFER; i++){
            if(buffer[i]=='#')
                break;
            /*The following code is for situations where the last line
             * of text is the same as what was found. If using fgets just
             * results in setting the file to the same line, then just need
             * to break the loop*/
            if(strstr(buffer,"TABLEAU:")!=0){
                fgets(buffer, MAX_BUFFER, input);
                if(strstr(buffer,"TABLEAU:")!=0)
                    break;
                i--;
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
                ptr[index].stock = 'F';
                index++;
            }
            else if(buffer[i] == '|'){
                ptr[index].rank = buffer[i];
                ptr[index].suit = 0;
                ptr[index].covered = 'F';
                ptr[index].stock = 'F';
                covered = 'F';
                index++;
            }
            if(strstr(buffer,"STOCK:")!=0){
                fputs(buffer,input);
                break;
            }
        }
        tabCol--;
        if(strstr(buffer,"STOCK:")!=0){
            break;
        }
        memset(buffer,0,MAX_BUFFER);
    }while(fgets(buffer, MAX_BUFFER, input) != 0 && tabCol != 0);
    if(isTableauCorrect() && tabCol == 0){
        return 1;
    }
    else{
        return 0;
    }
}
//Function for printing the tableau
void printTableau(){
    Card *ptr;
    for(int i = 7; i >= 1; i--){
        ptr = setPointer(i);
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

Card *getTopColCard(int col){
    /*Case 1: Column is empty
     * Case 2: Column is not empty*/
    Card *ptr = setPointer(col);
    if(ptr->rank == '|' && (ptr+1)->rank == '\0')
        return 0;
    while((ptr + 1)->rank != '\0'){
        ptr++;
    }
    return ptr;
}

void addCardToColumn(Card *ptr, int col){
    //assuming ptr is on the heap and not the stack
    Card *tabptr = setPointer(col);
    while(tabptr->rank != '\0'){
        tabptr++;
    }
    *tabptr = *ptr;
    free(ptr);
}