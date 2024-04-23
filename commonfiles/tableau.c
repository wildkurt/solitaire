//
// Created by wendellbest on 1/29/24.
//

#include <string.h>
#include "tableau.h"

/**For this part of the file, the columns will always be below the TABLEAU: header. Will need
 * to make sure that the cards for each line are put in the correct columns. Need to account for the '|' which is the
 * indicator that the cards following are face up. Foundations will exit once the last foundation block is found, so
 * still need to find the TABLEAU: header**/
void initializeTableau(Tableau *tableau){
    Card temp = {0,0,0};
    for(int i = 0; i < 22; i++){
        tableau->tab1[i] = temp;
        tableau->tab2[i] = temp;
        tableau->tab3[i] = temp;
        tableau->tab4[i] = temp;
        tableau->tab5[i] = temp;
        tableau->tab6[i] = temp;
        tableau->tab7[i] = temp;
    }
}


int getTableau(Tableau *tableau, int *line, FILE *filelink, char *buffer){
    char cleanBuffer[MAX_BUFFER] = {0};
    int column = 7;
    char faceup = 'f';

    initializeTableau(tableau);

    while(fgets(buffer, MAX_BUFFER, filelink)) {
        (*line)++;
        for(int i = 0; i < MAX_BUFFER && buffer[i] != '#' && buffer[i] != '\n'; i++){
            cleanBuffer[i] = buffer[i];
        }
        //Skip to the next line in file
        if(strstr(cleanBuffer, "TABLEAU:")!=0){
            continue;
        }
        Card *ptr = getPointerToColumn(column, tableau);
        for(int i = 0; i < MAX_BUFFER && cleanBuffer[i] != '\0'; i++){
            if(isRank(cleanBuffer[i]) && isSuit(cleanBuffer[i+1])){
                ptr->rank = cleanBuffer[i++];
                ptr->suit = cleanBuffer[i++];
                ptr->faceUp = faceup;
                ptr++;
            }
            if(cleanBuffer[i] == '|'){
                faceup = 't';
            }
        }
        Card *ptr2 = getPointerToColumn(column, tableau);
        if(checkIfColumnCorrect(ptr2)){
            return 1;
        }
        //Tests if the line contained a column or not. Every column will have a | even if empty
        if(faceup == 't')
            column--;
        //Once column 1 is found, no need to go further
        if(column == 0)
            break;
        faceup = 'f';
        memset(buffer,0,MAX_BUFFER);
        memset(cleanBuffer, 0, MAX_BUFFER);
    }
    if(column > 0)
        return 2;
    return 0;
}

Card *getPointerToColumn(int column, Tableau *tableau){
    switch(column){
        case 1 : return tableau->tab1;
        case 2 : return tableau->tab2;
        case 3 : return tableau->tab3;
        case 4 : return tableau->tab4;
        case 5 : return tableau->tab5;
        case 6 : return tableau->tab6;
        case 7 : return tableau->tab7;
        default : return 0;
    }
}

int checkIfColumnCorrect(Card *column){
    //treat column like a pointer and move pointer to a face up card
    if(column->rank == 0)
        return 0;
    while(column->faceUp == 'f')
        column++;
    //if the card after the current card is not empty and opposite colors, continue
    while((column + 1)->rank != 0){
        if(redAndBlack(column->rank, (column+1)->rank)){
            return 1;
        }
        column++;
    }

    return 0;
}

int redAndBlack(char suit1, char suit2){
    //if the chars are the same
    if(suit1 == suit2)
        return 1;
    if((suit1 == 'c' && suit2 == 's')||(suit1 == 's' && suit2 == 'c'))
        return 1;
    if((suit1 == 'd' && suit2 == 'h')||(suit1 == 'h' && suit2 == 'd'))
        return 1;
    return 0;
}

void printTableau(Tableau *tableau){
    printf("TABLEAU:\n");
    for(int i = 7; i >= 1; i--){
        Card *ptr = getPointerToColumn(i,tableau);
        printf("\t");
        if(ptr[0].rank == 0){
            printf("|\n");
            continue;
        }
        for(int j = 0; ptr[j].rank != 0; j++){
            if(j == 0 && ptr[j].faceUp == 't')
                printf("| ");
            if(ptr[j-1].faceUp == 'f' && ptr[j].faceUp == 't')
                printf("| ");
            printf("%c%c ", ptr[j].rank, ptr[j].suit);
        }
        printf("\n");
    }
}

void countTableauCards(Tableau *tableau, Card *countingdeck){
    int column = 7;
    Card *ptr;

    while(column != 0){
        ptr = getPointerToColumn(column, tableau);
        while(ptr->rank != 0){
            if(ptr->suit == 'c'){
                ptr->cardCount++;
                countingdeck[isRank(ptr->rank) - 1] = *ptr;
            }
            if(ptr->suit == 'd'){
                ptr->cardCount++;
                countingdeck[13 + isRank(ptr->rank) - 1] = *ptr;
            }
            if(ptr->suit == 'h'){
                ptr->cardCount++;
                countingdeck[26 + isRank(ptr->rank) - 1] = *ptr;
            }
            if(ptr->suit == 's'){
                ptr->cardCount++;
                countingdeck[39 + isRank(ptr->rank) - 1] = *ptr;
            }
            ptr++;
        }
        column--;
    }
}

void getTopTableauColumnCard(Tableau *tableau, char to, Card *destination){
    int columnNumber = to - '0';

    Card *ptr = getPointerToColumn(columnNumber, tableau);
    Card *startPtr = getPointerToColumn(columnNumber,tableau);
    while(ptr->rank != 0){ptr++;}

    if(ptr == startPtr){
        *destination = *ptr;
        return;
    }
    ptr--;
    *destination = *ptr;
}

void addCardToTableauColumn(Tableau *tableau, char to, Card *source){
    int columnNumber = to - '0';
    Card *ptr = getPointerToColumn(columnNumber, tableau);
    int i = 0;

    for(; ptr[i].rank != 0; i++){}
    ptr[i] = *source;
}
/**Tableau Rules:
 * 1. On first deal, only one card is up in each column. Columns start with the same number of cards  as the column number.
 * 2. Removing a card from a column that reveals a covered card mans the covered card is automatically turned over.
 * 3. Kings can only move to blank spaces, don't move King if it is the bottom card.
 * 4. Don't move a card if the card below it is face up and the same rank and color as the destination.
 * 5. Don't move cards with the same source and destination
 * */
int moveCardFromColumnToColumn(Tableau  *tableau, char from, char to){
    Card *fromPTR, *toPtr;
    fromPTR = getPointerToColumn(from - '0', tableau);
    toPtr = getPointerToColumn(to-'0', tableau);

    if(from == to){
        return 1;
    }
    if(fromPTR->rank == 'K' && toPtr->rank == 0){
        return 1;
    }

    return 0;
}

void removeCardFromColumn(Tableau *tableau, char column, Card source){
    int columnNumber = column - '0';
    Card temp = {0,0,0,0};

    Card *colptr = getPointerToColumn(columnNumber, tableau);

    while(colptr->rank != 0){
        if(isRank(colptr->rank) == isRank(source.rank) && colptr->suit == source.suit)
            break;
        colptr++;
    }
    if((colptr-1)->faceUp == 'f')
        (colptr-1)->faceUp = 't';
    *colptr = temp;
}
void printHumanReadCard(Card card){
    if(card.faceUp == 'f')
        printf("## ");
    else if(card.rank == 0)
        printf("-- ");
    else{
        printf("%c%c ", card.rank, card.suit);
    }
}

int noMoreCards(Card one, Card two, Card three, Card four, Card five, Card six, Card seven){
    int result = 0;
    result = one.rank + two.rank + three.rank + four.rank + five.rank + six.rank + seven.rank;
    if(result == 0)
        return 1;
    return 0;
}
void printHumanReadTableau(Tableau *tableau){
    for(int i = 0; i < 22; i++){
        if(noMoreCards(tableau->tab1[i], tableau->tab2[i], tableau->tab3[i], tableau->tab4[i], tableau->tab5[i], tableau->tab6[i], tableau->tab7[i]))
            break;
        printHumanReadCard(tableau->tab1[i]);
        printHumanReadCard(tableau->tab2[i]);
        printHumanReadCard(tableau->tab3[i]);
        printHumanReadCard(tableau->tab4[i]);
        printHumanReadCard(tableau->tab5[i]);
        printHumanReadCard(tableau->tab6[i]);
        printHumanReadCard(tableau->tab7[i]);
        printf("\n");
    }
}

void printTableauToFile(FILE *outputtofile, Tableau *tableau){
    Card *colptr;
    fprintf(outputtofile, "TABLEAU:\n");
    for(int i = 7; i > 0; i--){
        colptr = getPointerToColumn(i, tableau);
        fprintf(outputtofile,"\t");
        if(colptr->faceUp == 't')
            fprintf(outputtofile, "| ");
        if(colptr->rank == 0)
            fprintf(outputtofile, "|");
        while(colptr->rank != 0){
            if((colptr-1)->faceUp == 'f' && colptr->faceUp == 't')
                fprintf(outputtofile, "| ");
            fprintf(outputtofile, "%c%c ", colptr->rank, colptr->suit);
            colptr++;
        }
        fprintf(outputtofile,"\n");
    }

}