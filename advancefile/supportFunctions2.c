//
// Created by wendellbest on 3/8/22.
//

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "advance.h"
#include "../checkfile/foundation.h"
#include "../checkfile/tableau.h"
#include "../checkfile/stockWaste.h"

int flipCardStockToWaste(gameConfig *gameFile){
    Card *ptr;
    ptr = sw;
    while(ptr->rank != '|'){
        ptr++;
    }
    if((ptr+1)->rank == '\0'){
        return 1;
    }
    else{
        if(gameFile->turnOverThree != 'y'){
            Card temp;
            temp = *ptr;
            *ptr = *(ptr+1);
            *(ptr+1) = temp;
            return 0;
        }
        else{
            while((ptr+1)->rank != '\0'){
                Card temp;
                temp = *ptr;
                *ptr = *(ptr+1);
                *(ptr+1) = temp;
                ptr++;
            }
        }
    }
    return 0;
}

int resetWasteToStock(gameConfig *gameFile){
    if(gameFile->limitedGame == 'y' && gameFile->wasteResetsAllowed == 0){
        return 1;
    }
    Card *ptr;
    ptr = sw;
    while(ptr->rank != '|'){
        ptr++;
    }
    while((ptr-1)->rank != '\0'){
        Card temp = *ptr;
        *ptr = *(ptr-1);
        *(ptr-1) = temp;
        ptr--;
    }
    return 0;
}
Card *setCol(char c){

    if(c == '1'){
        return t1;
    }
    else if(c == '2'){
        return t2;
    }
    else if(c == '3'){
        return t3;
    }
    else if(c == '4'){
        return t4;
    }
    else if(c == '5'){
        return t5;
    }
    else if(c == '6'){
        return t6;
    }
    else if(c == '7'){
        return t7;
    }
    else if(c == 'w'){
        return sw;
    }
    else if(c == 'f'){
        return foundations;
    }
    return 0;
}

int moveColToCol(char source, char dest){
    //can't move from to same column
    if(source == dest){
        return 1;
    }
    //pointers
    Card *sourceCol, *destCol, *temp;
    //Helper function to set pointers to correct array
    sourceCol = setCol(source);
    destCol = setCol(dest);

    //move destination to end of array
    while((destCol+1)->rank != '\0'){
        destCol++;
    }
    //move source to covered cards indicator
    while(sourceCol->rank != '|'){
        sourceCol++;
    }
    //if there isn't another card, error
    if((sourceCol+1)->rank == '\0'){
        return 1;
    }
    //increment source pointer
    sourceCol++;
    //Case where the destination is empty
    if(destCol->rank == '|'){
        while(sourceCol->rank != 'K' && sourceCol->rank != '\0'){
            sourceCol++;
        }
        if(sourceCol->rank == '\0'){
            return 1;
        }
        temp = sourceCol;
        if((temp-1)->rank == '|' && (temp-1) != setCol(source)){
            Card tempC;
            tempC = *(temp-2);
            *(temp-2) = *(temp-1);
            *(temp-1) = tempC;
            (temp-1)->covered = 'n';
        }
        destCol++;
        while(temp->rank != '\0'){
            *destCol = *temp;
            destCol++;
            temp++;
        }
        while(sourceCol->rank != '\0'){
            sourceCol->rank = '\0';
            sourceCol->suit = '\0';
            sourceCol->covered = '\0';
            sourceCol->stock ='\0';
            sourceCol++;
        }
        return 0;
    }
    else{
        while((rankValue(sourceCol->rank)+1 != rankValue(destCol->rank))&&(isRedOrBlack(sourceCol->suit) !=
                                                                           isRedOrBlack(destCol->suit)) && (sourceCol->rank != '\0')){
            sourceCol++;
        }
        if(sourceCol->rank == '\0'){
            return 1;
        }
        destCol++;
        Card *temp;
        temp = sourceCol;
        while(temp->rank != '\0'){
            *destCol = *temp;
            destCol++;
            temp++;
        }
        if((sourceCol-1)->rank == '|' && (sourceCol-1)!= setCol(source)){
            *temp = *(sourceCol-1);
            *(sourceCol-1) = *(sourceCol-2);
            *(sourceCol-2) = *temp;
            (sourceCol-1)->covered = 'n';
        }
        while(sourceCol->rank != '\0'){
            sourceCol->rank = '\0';
            sourceCol->suit = '\0';
            sourceCol->covered = '\0';
            sourceCol->stock = '\0';
            sourceCol++;
        }
        return 0;
    }
}

int moveColToFoundation(char source){
    Card *temp;
    temp= setCol(source);
    while((temp+1)->rank != '\0'){
        temp++;
    }
    for(int i = 0; i < 4; i++){
        if(rankValue(temp->rank)-1 == rankValue(foundations[i].rank) && temp->suit == foundations[i].suit){
            foundations[i] = *temp;
            temp->rank = '\0';
            temp->suit = '\0';
            temp->covered = '\0';
            temp->stock = '\0';
            if((temp-1)->rank == '|' && (temp-1) != setCol(source)){
                Card tempC;
                tempC = *(temp-1);
                *(temp-1) = *(temp-2);
                *(temp-2) = tempC;
                (temp-1)->covered = 'n';
            }
            return 0;
        }
    }
    return 1;
}

int moveWasteToCol(char dest){
    Card *destination, *stockWaste;
    destination = setCol(dest);
    stockWaste = sw;

    while((stockWaste+1)->rank != '|'){
        stockWaste++;
    }
    if(destination->rank == '|' && (destination+1)->rank == '\0' && stockWaste->rank == 'K'){
        destination++;
        *destination = *stockWaste;
        while(stockWaste->rank != '\0'){
            *stockWaste = *(stockWaste+1);
            stockWaste++;
        }
        return 0;
    }
    else{
        while(destination->rank != '\0'){
            destination++;
        }
        if(rankValue(stockWaste->rank)+1 == rankValue((destination-1)->rank) && isRedOrBlack(stockWaste->suit) !=
                                                                                isRedOrBlack((destination-1)->suit)){
            *destination = *stockWaste;
            while(stockWaste->rank != '\0'){
                *stockWaste = *(stockWaste+1);
                stockWaste++;
            }
            return 0;
        }
    }
    return 1;
}

int moveWasteToFoundation(){
    Card *waste;
    waste = sw;

    while((waste+1)->rank != '|'){
        waste++;
    }

    for(int i = 0; i < 4; i++){
        if(rankValue(waste->rank) == rankValue(foundations[i].rank) + 1 && waste->suit == foundations[i].suit){
            foundations[i] = *waste;
            while(waste->rank != '\0'){
                *waste = *(waste + 1);
                waste++;
            }
            return 0;
        }
    }
    return 1;
}

int performMoves(char source, char dest){
    if(source == 'f' || dest == 'w'){
        return 1;
    }
    if(isdigit(source)){
        if(isdigit(dest)){
            if(moveColToCol(source,dest)){
                return 1;
            }
        }
        else{
            if(moveColToFoundation(source)){
                return 1;
            }
        }
    }
    else if(isalpha(source)){
        if(isdigit(dest)){
            if(moveWasteToCol(dest)){
                return 1;
            }
        }
        else if(isalpha(dest)){
            if(moveWasteToFoundation()){
                return 1;
            }
        }
    }
    return 0;
}

void processMoves(char *buffer, FILE *input, gameConfig *gameFile){
    do{
        for(int i = 0; buffer[i]!='\n'; i++){
            if(gameFile->limitOnMoves == 'y' && gameFile->moves == 0)
                break;
            if(buffer[i]=='.'){
                gameFile->totalMoves++;
                gameFile->moves--;
                if(flipCardStockToWaste(gameFile)){
                    fprintf(stderr,"Move %d is illegal: %c\n", gameFile->totalMoves, buffer[i]);
                    if(gameFile->printToExchange == 'y')
                        writeToExchange(gameFile);
                    else
                        writeHumanReadable(gameFile);
                    exit(1);
                }
            }
            else if(buffer[i] == 'r'){
                gameFile->totalMoves++;
                gameFile->moves--;
                if(resetWasteToStock(gameFile)){
                    fprintf(stderr,"Wove %d is illegal: %c\n",gameFile->totalMoves,buffer[i]);
                    if(gameFile->printToExchange == 'y')
                        writeToExchange(gameFile);
                    else
                        writeHumanReadable(gameFile);
                    exit(1);
                }
            }
            else if(isalnum(buffer[i]) && buffer[i+1] == '-' && buffer[i+2] == '>' && isalnum(buffer[i+3])){
                gameFile->totalMoves++;
                gameFile->moves--;
                if(performMoves(buffer[i], buffer[i+3])){
                    fprintf(stderr, "Move %d is illegal: %c%c%c%c\n",gameFile->totalMoves,buffer[i],buffer[i+1],buffer[i+2], buffer[i+3]);
                    if(gameFile->printToExchange == 'y')
                        writeToExchange(gameFile);
                    else
                        writeHumanReadable(gameFile);
                    exit(1);
                }
            }
        }
    }while(fgets(buffer, MAX_SIZE, input)!=0);
}
void writeTableau(FILE *out, Card *ptr){
    fprintf(out," ");
    for(int i = 0; ptr[i].rank != '\0'; i++){
        if(ptr[i].rank == '|')
            fprintf(out," %c",ptr[i].rank);
        else
            fprintf(out," %c%c",ptr[i].rank, ptr[i].suit);
    }
    fprintf(out,"\n");
}

void writeToFile(gameConfig *gameFile){
    FILE *out;
    int num = 1;
    out = fopen(gameFile->outputFile, "w");
    fprintf(out, "RULES:\n");
    if(gameFile->turnOverThree == 'y'){
        num = 3;
    }
    fprintf(out, "  turn %d\n",num);
    if(gameFile->limitedGame == 'y'){
        fprintf(out,"  limit %d\n",gameFile->wasteResetsAllowed);
    }
    else{
        fprintf(out,"  unlimited\n");
    }
    fprintf(out,"FOUNDATIONS:\n");
    for(int i = 0; i < 4; i++){
        fprintf(out,"  %c%c",foundations[i].rank,foundations[i].suit);
    }
    fprintf(out,"\n");
    fprintf(out, "TABLEAU:\n");
    Card *ptr;
    ptr = t7;
    writeTableau(out,ptr);
    ptr = t6;
    writeTableau(out,ptr);
    ptr = t5;
    writeTableau(out,ptr);
    ptr = t4;
    writeTableau(out,ptr);
    ptr = t3;
    writeTableau(out,ptr);
    ptr = t2;
    writeTableau(out,ptr);
    ptr = t1;
    writeTableau(out,ptr);
    fprintf(out,"STOCK:\n");
    ptr = sw;
    writeTableau(out,ptr);
    fprintf(out,"MOVES:\n");
}

void writeToExchange(gameConfig *gameFile){
    printf("RULES:\n");
    if(gameFile->turnOverThree == 'y')
        printf("  turn 3\n");
    else
        printf("  turn 1\n");
    printf("FOUNDATIONS:\n");
    printFoundation();
    printf("TABLEAU:\n");
    printTableau();
    printf("STOCK:\n");
    printStockWaste();
    printf("MOVES:\n");
}

void writeHumanReadable(gameConfig *gameFile){
    Card *one, *two, *three, *four, *five, *six, *seven;
    one = t1;
    two = t2;
    three = t3;
    four = t4;
    five = t5;
    six = t6;
    seven = t7;

    printf("Foundations\n");
    printFoundation();
    printf("Tableau\n");

    while(1){
        if(one->rank == '\0' && two->rank == '\0' && three->rank == '\0' &&
           four->rank == '\0' && five->rank == '\0' && six->rank == '\0' && seven->rank == '\0'){
            break;
        }
        //column one
        if(one->rank == '|'){
            one++;
        }
        if(one->covered == 'y'){
            printf("## ");
            one++;
        }
        else if(one->rank == '\0'){
            printf(".. ");
            one++;
        }
        else{
            printf("%c%c ",one->rank, one->suit);
            one++;
        }
        //column two
        if(two->rank == '|'){
            two++;
        }
        if(two->covered == 'y'){
            printf("## ");
            two++;
        }
        else if(two->rank == '\0'){
            printf(".. ");
            two++;
        }
        else{
            printf("%c%c ",two->rank, two->suit);
            two++;
        }
        //column three
        if(three->rank == '|'){
            three++;
        }
        if(three->covered == 'y'){
            printf("## ");
            three++;
        }
        else if(three->rank == '\0'){
            printf(".. ");
            three++;
        }
        else{
            printf("%c%c ",three->rank, three->suit);
            three++;
        }
        //column four
        if(four->rank == '|'){
            four++;
        }
        if(four->covered == 'y'){
            printf("## ");
            four++;
        }
        else if(four->rank == '\0'){
            printf(".. ");
            four++;
        }
        else{
            printf("%c%c ",four->rank, four->suit);
            four++;
        }
        //column five
        if(five->rank == '|'){
            five++;
        }
        if(five->covered == 'y'){
            printf("## ");
            five++;
        }
        else if(five->rank == '\0'){
            printf(".. ");
            five++;
        }
        else{
            printf("%c%c ",five->rank, five->suit);
            five++;
        }
        //column six
        if(six->rank == '|'){
            six++;
        }
        if(six->covered == 'y'){
            printf("## ");
            six++;
        }
        else if(six->rank == '\0'){
            printf(".. ");
            six++;
        }
        else{
            printf("%c%c ",six->rank, six->suit);
            six++;
        }
        //column seven
        if(seven->rank == '|'){
            seven++;
        }
        if(seven->covered == 'y'){
            printf("## ");
            seven++;
        }
        else if(seven->rank == '\0'){
            printf(".. ");
            seven++;
        }
        else{
            printf("%c%c ",seven->rank, seven->suit);
            seven++;
        }
        printf("\n");
    }
    printf("Waste top\n");
    for(int i = 0; sw[i].rank != '|'; i++){
        printf("%c%c ", sw[i].rank, sw[i].suit);
    }
    printf("\n");
}

