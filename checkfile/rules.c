//
// Created by wendellbest on 11/1/23.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "check.h"
#include "rules.h"

void findRules(char *file, Rules *rules){
    FILE *inputFile;

    char buffer[MAX_BUFFER] = {0}, trimBuffer[MAX_BUFFER] = {0};
    inputFile = fopen(file,"r");
    if(inputFile == 0){
        fprintf(stderr, "%s not found", file);
        exit(1);
    }

    while(fgets(buffer, MAX_BUFFER, inputFile)){
        int index = 0;
        for(int i = 0; i < MAX_BUFFER; i++){
            if(buffer[i] != '#' && buffer[i] != 0)
                trimBuffer[index++] = buffer[i];
            else
                break;
        }
        if(strstr(trimBuffer, "turn 1") != 0){
            rules->turnOver = 1;
            rules->found++;
        }
        else if(strstr(trimBuffer, "turn 3") != 0){
            rules->turnOver = 3;
            rules->found++;
        }
        else if(strstr(trimBuffer, "limit ") != 0){
            char charNumber[10] = {0};
            int subIndex = strspn(trimBuffer, "limit "), index2 = 0;
            while(isdigit(trimBuffer[subIndex])){
                charNumber[index2++] = trimBuffer[subIndex++];
            }
            rules->limit = atoi(charNumber);
            rules->found++;
        }
        else if(strstr(trimBuffer, "unlimited")!= 0){
            rules->limit = -1;
            rules->found++;
        }
        if(rules->found == 2)
            break;
        memset(trimBuffer,0,MAX_BUFFER);
    }
}

void printRulesSTDOUT(Rules rules){
    printf("RULES:\n");
    printf("Turn %d\n", rules.turnOver);
    printf("Limit / Unlimited: %d\n", rules.limit);
}