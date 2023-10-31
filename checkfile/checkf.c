//
// Created by wendellbest on 5/30/22.
//

#include <string.h>
#include "check.h"
#include "card.h"
#include "stockWaste.h"
#include "tableau.h"
#include "foundation.h"

void readFile(char *file, Rules *rules){
    FILE *input;
    char buffer[MAX_BUFFER], readBuffer[MAX_BUFFER];
    char *lim;
    int found = 0, line = 0, index = 0 ;
    if(strlen(file)!=0)
        input = fopen(file,"r");
    else
        input = stdin;

    if(input == 0){
        fprintf(stderr, "Unable to open %s", file);
    }

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
            found++;
        }
        //I made a Rules struct, not necessary for check, but trying to lean forward
        //Checks for Turn 1 or Turn 3
        if(strstr(readBuffer, "turn 1") != 0){
            if(found < 1){ //1 if RULES: found
                fprintf(stderr,"Rules not found line %d\n", line);
                rules->line = line;
                rules->found = found;
            }
            rules->turnOver = 1;
            found++;
        }
        if(strstr(readBuffer, "turn 3") != 0){
            if(found < 1){ //1 if RULES: found
                fprintf(stderr,"Rules not found line %d\n", line);
                rules->line = line;
                rules->found = found;
            }
            rules->turnOver = 3;
            found++;
        }
        //Checks for limit N or unlimited
        if(strstr(readBuffer, "unlimited") != 0){
            if(found < 2){ //2 if turns found
                fprintf(stderr,"Turn not found or incorrect line %d\n", line);
                rules->line = line;
                rules->found = found;
            }
            rules->limit = -1;
            found++;
        }
        //I needed to do it this way so I could use scanf to get the number from the
        //string, and if the number is bigger than one digit.
        lim = strstr(readBuffer, "limit ");
        if(lim != 0){
            if(found < 2){ //2 if turns found
                fprintf(stderr,"Turn not found line %d\n", line);
                rules->line = line;
                rules->found = found;
            }
            int bob = 0;
            char string[10];
            sscanf(lim,"%s %d", string, &bob);
            rules->limit = bob;
            found++;
        }
        //Foundations
        if(strstr(readBuffer, "FOUNDATIONS:") != 0){
            if(found < 3){ // 3 if limits found
                fprintf(stderr,"Limit not found line %d\n", line);
                rules->line = line;
                rules->found = found;
            }
            found++;
            //This is where the foundations functions take over
            if(!findFoundations(readBuffer, input, &line)){
                fprintf(stderr,"Foundations are incorrect or incomplete line %d\n", line);
                rules->line = line;
                rules->found = found;
            }
            //printFoundation();
            found++;
        }
        //Tableau
        if(strstr(readBuffer, "TABLEAU:") != 0){
            if(found < 5){ // 5 if TABLEAU: and the tableaus found
                fprintf(stderr,"Foundations not found line %d\n", line);
                rules->line = line;
                rules->found = found;
            }
            found++;
            if(!findTableau(readBuffer, input, &line)){
                fprintf(stderr, "TABLEAU: not found or tableau is incorrect line %d\n",line);
                printTableau();
                rules->line = line;
                rules->found = found;
            }

            found++;
        }
        //STOCK:
        if(strstr(readBuffer, "STOCK:") != 0){
            if(found < 7){
                fprintf(stderr, "TABLEAU: not found or tableau is incorrect line %d\n",line);
                rules->line = line;
                rules->found = found;
            }
            found++;
            if(!findStockWaste(readBuffer, input, &line)){
                fprintf(stderr, "Stock not found or stock is incorrect line %d\n",line);
                rules->line = line;
                rules->found = found;
            }
            //printStockWaste();
            found++;
        }
        //MOVES:
        if(strstr(readBuffer, "MOVES:") != 0){
            found++;
            break;
        }
        memset(buffer,0,MAX_BUFFER);
        memset(readBuffer,0,MAX_BUFFER);
    }
    rules->line = line;
    rules->found = found;
    fclose(input);
}

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
    ptr = stockWastePtr();
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
int missingDuplicateCards(){
    int deck[52] = {0};
    int total = 0, missing = 0, duplicates = 0;
    Card *ptrfd = fdPtr();
    for(int i = 0; i < 4; i++){
        if(ptrfd[i].rank == '_')
            continue;
        int limit = rankValue(ptrfd[i].rank);
        for(int j = limit; j >=0 ; j--){
            deck[j + indexSetter(ptrfd[i].suit)]  += 1;
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
    ptr = stockWastePtr();
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

Rules findRules(char *file){
    FILE *inputFile;
    Rules temp = {0, 0, 0, 0};
    char buffer[MAX_BUFFER] = {0}, trimBuffer[MAX_BUFFER] = {0};
    inputFile = fopen(file,"r");

    while(fgets(buffer, MAX_BUFFER, inputFile)){
        int index = 0;
        for(int i = 0; i < MAX_BUFFER; i++){
            if(buffer[i] != '#')
                trimBuffer[index++] = buffer[i];
        }
        if(strcmp(trimBuffer, "turn 1") == 0){
            temp.turnOver = 1;
            temp.found++;
        }
        else if(strcmp(trimBuffer, "turn 3") == 0){
            temp.turnOver = 3;
            temp.found++;
        }
        else if(strcmp(trimBuffer, "limit ") == 0){
            scanf(buffer, "%s* %d", temp.limit);
            temp.found++;
        }
        else if(strcmp(trimBuffer, "unlimited")){
            temp.limit = -1;
            temp.found++;
        }
        if(temp.found == 2)
            break;
    }
    return temp;
}