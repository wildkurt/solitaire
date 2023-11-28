//
// Created by wendellbest on 11/22/23.
//

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "rules.h"

int findRules(char *buffer, char *readBuffer, FILE *file, int *line, Rules *rules){

    while(fgets(buffer, MAX_BUFFER, file)){
        int index = 0;
        (*line)++;
        for(int i = 0; i < MAX_BUFFER; i++){
            if(buffer[i] != '#' && buffer[i] != '\n')
                readBuffer[index++] = buffer[i];
            else
                break;
        }
        if(strstr(readBuffer, "FOUNDATIONS:")){
            fputs(buffer,file);
            break;
        }
        if(strstr(readBuffer, "turn 1") != 0){
            if(rules->found < 1){
                fprintf(stderr, "Rules not found line %d", *line);
                return 0;
            }
            else{
                rules->turnOver = 1;
                rules->found++;
            }
        }
        else if(strstr(readBuffer, "turn 3") != 0){
            if(rules->found < 1){
                fprintf(stderr, "Rules not found line %d", *line);
                return 0;
            }
            else{
                rules->turnOver = 3;
                rules->found++;
            }

        }
        else if(strstr(readBuffer, "limit ") != 0){
            char charNumber[10] = {0};
            if(rules->found < 2){
                fprintf(stderr,"Turn rule not found at line %d", *line);
                return(0);
            }
            else{
                int subIndex = strspn(readBuffer, "limit "), index2 = 0;
                while(isdigit(readBuffer[subIndex])){
                    charNumber[index2++] = readBuffer[subIndex++];
                }
                rules->limit = atoi(charNumber);
                rules->found++;
            }

        }
        else if(strstr(readBuffer, "unlimited")!= 0){
            if(rules->found < 2){
                fprintf(stderr,"Turn rule not found at line %d", *line);
                return(0);
            }
            else{
                rules->limit = -1;
                rules->found++;
            }
        }
        memset(readBuffer,0,MAX_BUFFER);
    }
    if(rules->found == 3)
        return 1;
    else
        return 0;
}

void printRulesSTDOUT(Rules *rules){
    printf("RULES:\n");
    printf("Turn %d\n", rules->turnOver);
    printf("Limit / Unlimited: %d\n", rules->limit);
}