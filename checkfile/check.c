//
// Created by wende on 5/30/2022.
//
#include <stdio.h>
#include <string.h>
#include "check.h"
#include "foundation.h"
#include "tableau.h"

int main(int args, char *argv[]){
    FILE *input;
    char buffer[50];
    Rules rules;
    char *lim;
    int found = 0, line = 0;
    if(args < 2){
        input = fopen((const char *) stdin, "r");
    }
    else{
        input = fopen(argv[1], "r");
    }
    if(input == 0){
        fprintf(stderr, "Unable to open file %s\n", argv[1]);
        return 1;
    }
    while(fgets(buffer, 50, input) != 0){
        line++;
        if(strstr(buffer, "RULES:") != 0){
            found++;
        }
        if(strstr(buffer, "turn 1") != 0){
            if(found < 1){ //1 if RULES: found
                fprintf(stderr,"Rules not found line %d\n", line);
                return 1;
            }
            rules.turnOver = 1;
            found++;
        }
        if(strstr(buffer, "turn 3") != 0){
            if(found < 1){ //1 if RULES: found
                fprintf(stderr,"Rules not found line %d\n", line);
                return 1;
            }
            rules.turnOver = 3;
            found++;
        }
        if(strstr(buffer, "unlimited") != 0){
            if(found < 2){ //2 if turns found
                fprintf(stderr,"Turn not found line %d\n", line);
                return 1;
            }
            rules.limit = -1;
            found++;
        }
        lim = strstr(buffer, "limit ");
        if(lim != 0){
            if(found < 2){ //2 if turns found
                fprintf(stderr,"Turn not found line %d\n", line);
                return 1;
            }
            int bob = 0;
            char string[10];
            sscanf(lim,"%s %d", string, &bob);
            rules.limit = bob;
            found++;
        }
        if(strstr(buffer, "FOUNDATIONS:") != 0){
            if(found < 3){ // 3 if limits found
                fprintf(stderr,"Limit not found line %d\n", line);
                return 1;
            }
            found++;
            if(!findFoundations(buffer, input, &line)){
                fprintf(stderr,"Foundations are incorrect or incomplete line %d\n", line);
                return 1;
            }
            found++;
        }
        if(strstr(buffer, "TABLEAU:") != 0){
            if(found < 5){ // 5 if TABLEAU: and the tableaus found
                fprintf(stderr,"Foundations not found line %d\n", line);
                return 1;
            }
            found++;
            if(!findTableau(buffer, input, &line)){
                fprintf(stderr, "TABLEAU: not found or tableau is incorrect line %d\n",line);
                return 1;
            }
            found++;
        }
        printTableau();
        if(strstr(buffer, "STOCK:") != 0){
            printf("%s", buffer);
        }
        if(strstr(buffer, "MOVES:") != 0){
            printf("%s", buffer);
        }
        memset(buffer,0,50);
    }
    printf("Turn over: %d, Limit: %d\n", rules.turnOver, rules.limit);
    fclose(input);
    return 0;
}