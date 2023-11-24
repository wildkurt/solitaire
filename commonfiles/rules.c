//
// Created by wendellbest on 11/22/23.
//

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "rules.h"

int findRules(char *buffer, FILE *file, int *line, Rules *rules){
    char trimBuffer[MAX_BUFFER] = {0};

    while(fgets(buffer, MAX_BUFFER, file)){
        int index = 0;
        *line++;
        for(int i = 0; i < MAX_BUFFER; i++){
            if(buffer[i] != '#' && buffer[i] != 0)
                trimBuffer[index++] = buffer[i];
            else
                break;
        }

        if(strstr(trimBuffer, "turn 1") != 0){
            if(rules->found < 1){
                fprintf(stderr, "Rules not found line %d", *line);
                return 0;
            }
            else{
                rules->turnOver = 1;
                rules->found++;
            }
        }
        else if(strstr(trimBuffer, "turn 3") != 0){
            if(rules->found < 1){
                fprintf(stderr, "Rules not found line %d", *line);
                return 0;
            }
            else{
                rules->turnOver = 3;
                rules->found++;
            }

        }
        else if(strstr(trimBuffer, "limit ") != 0){
            char charNumber[10] = {0};
            if(rules->found < 2){
                fprintf(stderr,"Turn rule not found at line %d", *line);
                return(0);
            }
            else{
                int subIndex = strspn(trimBuffer, "limit "), index2 = 0;
                while(isdigit(trimBuffer[subIndex])){
                    charNumber[index2++] = trimBuffer[subIndex++];
                }
                rules->limit = atoi(charNumber);
                rules->found++;
            }

        }
        else if(strstr(trimBuffer, "unlimited")!= 0){
            if(rules->found < 2){
                fprintf(stderr,"Turn rule not found at line %d", *line);
                return(0);
            }
            else{
                rules->limit = -1;
                rules->found++;
            }
        }
        if(rules->found == 3)
            return 1;
        memset(trimBuffer,0,MAX_BUFFER);
    }
}

void printRulesSTDOUT(Rules *rules){
    printf("RULES:\n");
    printf("Turn %d\n", rules->turnOver);
    printf("Limit / Unlimited: %d\n", rules->limit);
}