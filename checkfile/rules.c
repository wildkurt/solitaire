//
// Created by wendellbest on 11/1/23.
//

#include <stdio.h>
#include <string.h>
#include "check.h"
#include "rules.h"

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

void printRulesSTDOUT(Rules rules){
    printf("RULES:\n");
    printf("Turn %d\n", rules.turnOver);
    printf("Limit / Unlimited: %d\n", rules.limit);
}