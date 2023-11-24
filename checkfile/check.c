//
// Created by wendellbest on 11/22/23.
//

#include <stdio.h>
#include <string.h>
#include "check.h"

void readFile(char *inputFile, GameConfiguration *game){
    FILE *input;
    char buffer[MAX_BUFFER] = {0}, readBuffer[MAX_BUFFER]={0};
    int line = 0, index = 0 ;
    if(strlen(inputFile)!=0)
        input = fopen(inputFile,"r");
    else
        input = stdin;

    if(input == 0){
        fprintf(stderr, "Unable to open %s", inputFile);
    }
    //Reads line from file
    while(fgets(buffer, MAX_BUFFER, input) != 0){
        line++;
        //Ignore hashes
        for(int i = 0; i < MAX_BUFFER; i++){
            if(buffer[i] != '#' && buffer[i] != '\0'){
                readBuffer[index++] = buffer[i];
            }
            else{
                index = 0;
                break;
            }
        }
        //RULES:
        if(strstr(readBuffer, "RULES:") != 0){
            game->found++;
            game->rules.found++;
            if(!findRules(buffer, input, &line, &game->rules)){
                return;
            }
        }
        //Foundations
        if(strstr(readBuffer, "FOUNDATIONS:") != 0){
            if(game->found < 1){ // 1 if rules found
                fprintf(stderr,"Error at line: %d\n", line);
                return;
            }
            game->found++;
            //This is where the foundations functions take over
            if(!findFoundation(readBuffer, input, &line, &game->foundation)){
                fprintf(stderr,"Foundations are incorrect or incomplete line %d\n", line);
                return;
            }
            //printFoundation();
        }
        //Tableau
        if(strstr(readBuffer, "TABLEAU:") != 0){
            if(game->found < 2){ // 2 if TABLEAU: and the tableaus found
                fprintf(stderr,"Foundations not found line %d\n", line);
                return;
            }
            game->found++;
            if(!findTableau(readBuffer, input, &line, &game->tableau)){
                fprintf(stderr, "TABLEAU: not found or tableau is incorrect line %d\n",line);
                return;
            }
        }
        //STOCK:
        if(strstr(readBuffer, "STOCK:") != 0){
            if(game->found < 3){
                fprintf(stderr, "TABLEAU: not found or tableau is incorrect line %d\n",line);
                return;
            }
            game->found++;
            if(!findStockWaste(readBuffer, input, &line, &game->stockwaste)){
                fprintf(stderr, "Stock not found or stock is incorrect line %d\n",line);
                return;
            }
            //printStockWaste();
        }
        //MOVES:
        if(strstr(readBuffer, "MOVES:") != 0){
            game->found++;
            return;
        }
        memset(buffer,0,MAX_BUFFER);
        memset(readBuffer,0,MAX_BUFFER);
    }
    fclose(input);
}

void countCards(int *covered, int *stock, int *waste, GameConfiguration *game){
    Card *ptr;
    int col = 7;
    while(col != 0){
        ptr = setPointer(col, &game->tableau);
        while(ptr->rank != '\0'){
            if(ptr->covered == 'T')
                *covered = *covered + 1;
            ptr++;
        }
        col--;
    }
    ptr = stockWastePtr(&game->stockwaste);
    while(ptr->rank != '\0'){
        if(ptr->stock == 'T'){
            *stock = *stock + 1;
            *covered = *covered + 1;
        }
        else if(ptr->rank != '|')
            *waste = *waste + 1;
        ptr++;
    }
}

int indexSetter(char c){
    switch (c){
        case 'c' : return 0;
        case 'd' : return 13;
        case 'h' : return 26;
        case 's' : return 39;
        default: return -1;
    }
}

int missingDuplicateCards(GameConfiguration *game){
    int deck[52] = {0};
    //Total counts all the cards
    int missing = 0, duplicates = 0;

    //get a pointer to the foundations
    Card *ptrfd = fdPtr(&game->foundation);
    for(int i = 0; i < 4; i++){
        if(ptrfd[i].rank == '_')
            continue;
        int limit = rankValue(ptrfd[i].rank);
        for(int j = limit; j >=0 ; j--){
            deck[j + indexSetter(ptrfd[i].suit)]  += 1;
        }
    }
    //count the cards in the Tableau
    Card *ptr;
    int col = 7;
    while(col != 0){
        ptr = setPointer(col, &game->tableau);
        while(ptr->rank != '\0'){
            if(ptr->rank != '|')
                deck[rankValue(ptr->rank) + indexSetter(ptr->suit)] += 1;
            ptr++;
        }
        col--;
    }
    //count the cards in the stock
    ptr = stockWastePtr(&game->stockwaste);
    while(ptr->rank != '\0'){
        if(ptr->rank != '|')
            deck[rankValue(ptr->rank) + indexSetter(ptr->suit)] += 1;
        ptr++;
    }

    for(int i = 0; i < 52; i++){
        if(deck[i] > 1)
            duplicates++;
        else if(deck[i] == 0)
            missing++;
    }

    if(missing > 0){
        printf("Missing cards: ");
        char l;
        int offset = 0;
        for(int i = 0; i < 52; i++){
            if(i < 13){l = 'c';}
            if(i >= 13 && i < 26){offset = 13; l = 'd';}
            if(i >= 26 && i < 39){offset = 26; l = 'h';}
            if(i >= 39){offset = 39; l = 's';}
            if(deck[i] == 0){
                printf("%c%c ", valueRank(i - offset),l);
            }
        }
        printf("\n");
    }
    if(duplicates > 0){
        printf("Duplicate cards:");
        char l;
        int offset = 0;
        for(int i = 0; i < 52; i++){
            if(i < 13){l = 'c';}
            if(i >= 13 && i < 26){offset = 13; l = 'd';}
            if(i >= 26 && i < 39){offset = 26; l = 'h';}
            if(i >= 39){offset = 39; l = 's';}
            if(deck[i] > 1){
                printf("%c%c ", valueRank(i - offset),l);
            }
        }
        printf("\n");
    }
    return 1;
}