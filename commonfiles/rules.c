//
// Created by wendellbest on 1/29/24.
//

#include <string.h>
#include <stdlib.h>
#include "rules.h"

int getRules(Rules *rules, int *line, FILE *filename, char *buffer) {
    //Buffer to strip # lines
    char cleanBuffer[MAX_BUFFER];
    // Indicates if section is found
    int found = 0;

    //Read each line from the file
    while(fgets(buffer,MAX_BUFFER, filename)){
        //Skip lines that start with # or ignore everything after #
        for(int i = 0; buffer[i] != '#' && i < MAX_BUFFER; i++){
            cleanBuffer[i] = buffer[i];
        }
        //Put the contents of the cleanbuffer into buffer and return to caller
        if(strstr(cleanBuffer,"FOUNDATIONS:") != 0){
            break;
        }
        //Look for RULES: header, card turn over, and waste resets
        if(strstr(cleanBuffer, "RULES:")!=0){
            found++;
            continue;
        }
        //If turn is found
        if(strstr(cleanBuffer, "turn") != 0){
            //if RULES: was not found then return error
            if(found != 1){
                return 1;
            }
            //Determine which turn it is
            else{
                if(strstr(cleanBuffer, "turn 1") != 0){
                    found++;
                    rules->cardTurnover = 1;
                }
                else if(strstr(cleanBuffer, "turn 3") != 0){
                    found++;
                    rules->cardTurnover = 3;
                }
            }
        }
        //look for waste resets
        if(strstr(cleanBuffer,"limit")!=0){
            //if Rules or turn not found, error
            if(found != 2)
                return 2;
            if(strstr(cleanBuffer,"unlimited") != 0){
                found++;
                rules->wasteResets = -1;
            }
            else{
                //get the number of allowed resets
                char *ptr = strstr(cleanBuffer,"limit ");
                ptr+=6;
                char *endPtr;
                rules->wasteResets = strtol(ptr,&endPtr, 10);
            }
        }
        *line++;
        memset(buffer,0,MAX_BUFFER);
        memset(cleanBuffer, 0, MAX_BUFFER);
    }
    if(found != 3)
        return 3;
    //FOUNDATIONS: should be in the cleanBuffer minus any #. Copy to the buffer so next function can continue searching
    memset(buffer, 0 , MAX_BUFFER);
    strcpy(buffer, cleanBuffer);
    return 0;
}