//
// Created by wendellbest on 5/30/22.
//
#include "check.h"
#include "card.h"
#include "stockWaste.h"
#include "tableau.h"
#include "foundation.h"

void countCards(int *covered, int *stock, int *waste){
    Card *ptr;
    int col = 7;
    while(col != 0){
        ptr = setPointer(col);
        while(ptr->rank != '\0'){
            if(ptr->covered == 'T')
                *covered = *covered + 1;
            ptr++;
        }
        col--;
    }
    ptr = sw;
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
    }
}
int missingDuplicateCards(){
    int deck[52] = {0};
    int total = 0, missing = 0, duplicates = 0;

    for(int i = 0; i < 4; i++){
        if(fd[i].rank == '_')
            continue;
        int limit = rankValue(fd[i].rank);
        for(int j = limit; j >=0 ; j--){
            deck[j + indexSetter(fd[i].suit)]  += 1;
        }
    }
    Card *ptr;
    int col = 7;
    while(col != 0){
        ptr = setPointer(col);
        while(ptr->rank != '\0'){
            if(ptr->rank != '|')
                deck[rankValue(ptr->rank) + indexSetter(ptr->suit)] += 1;
            ptr++;
        }
        col--;
    }
    ptr = sw;
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
        else
            total++;
    }
    if(total == 52)
        return 0;
    else if(missing > 0){
        printf("Missing cards: ");
        char l;
        int offset = 0;
        for(int i = 0; i < 52; i++){
            if(i < 13){offset = 0; l = 'c';}
            else if(i >= 13 && i < 26){offset = 13; l = 'd';}
            else if(i >= 26 && i < 39){offset = 26; l = 'h';}
            else if(i >= 39 && i < 52){offset = 39; l = 's';}
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
            if(i < 13){offset = 0; l = 'c';}
            else if(i >= 13 && i < 26){offset = 13; l = 'd';}
            else if(i >= 26 && i < 39){offset = 26; l = 'h';}
            else if(i >= 39 && i < 52){offset = 39; l = 's';}
            if(deck[i] > 1){
                printf("%c%c ", valueRank(i - offset),l);
            }
        }
        printf("\n");
    }
    return 1;
}