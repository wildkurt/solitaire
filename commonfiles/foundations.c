//
// Created by wendellbest on 1/29/24.
//

#include <string.h>
#include "foundations.h"

/**Find the foundations if they are in horizontal or vertical orientation. They must be in the correct order clubs,
 * diamonds, hearts, and spades. Rank can be empty "_". **/
int getFoundations(Foundations *foundation, int *line, FILE *filelink, char *buffer){
    //Since FOUNDATIONS: should be in buffer, need to check for it and any cards first
    int found = 0;
    char cleanBuffer[MAX_BUFFER] = {0};
    do{
        for(int i = 0; i < MAX_BUFFER && buffer[i] != '#' && buffer[i] != '\0'; i++){
            cleanBuffer[i]=buffer[i];
        }
        if(strstr(cleanBuffer, "FOUNDATIONS:") != 0){
            found++;
        }
        for(int i = 0; cleanBuffer[i]!= '\0'; i++){
            if(found == 1 && cleanBuffer[i] == 'c'){
                if(isRank(cleanBuffer[i-1]) || cleanBuffer[i-1] =='_'){
                    foundation->foundation[0].suit = cleanBuffer[i];
                    foundation->foundation[0].rank = cleanBuffer[i-1];
                    found++;
                }
            }
            else if(found == 0 && cleanBuffer[i] == 'c' && (isRank(cleanBuffer[i-1]) || cleanBuffer[i-1] == '_')){
                return 1;
            }
            if(found == 2 && cleanBuffer[i] == 'd'){
                if(isRank(cleanBuffer[i-1]) || cleanBuffer[i-1] == '_'){
                    foundation->foundation[1].suit = cleanBuffer[i];
                    foundation->foundation[1].rank = cleanBuffer[i-1];
                    found++;
                }
            }
            else if(found == 1 && cleanBuffer[i] == 'd' && (isRank(cleanBuffer[i-1]) || cleanBuffer[i-1] == '_')){
                return 2;
            }
            if(found == 3 && cleanBuffer[i] == 'h'){
                if(isRank(cleanBuffer[i-1]) || cleanBuffer[i-1] == '_'){
                    foundation->foundation[2].suit = cleanBuffer[i];
                    foundation->foundation[2].rank = cleanBuffer[i-1];
                    found++;
                }
            }
            else if(found == 2 && cleanBuffer[i] == 'h' && (isRank(cleanBuffer[i-1]) || cleanBuffer[i-1] == '_')){
                return 2;
            }
            if(found == 4 && cleanBuffer[i] == 's'){
                if(isRank(cleanBuffer[i-1]) || cleanBuffer[i-1] == '_'){
                    foundation->foundation[3].suit = cleanBuffer[i];
                    foundation->foundation[3].rank = cleanBuffer[i-1];
                    found++;
                }
            }
            else if(found == 3 && cleanBuffer[i] == 'h' && (isRank(cleanBuffer[i-1]) || cleanBuffer[i-1] == '_')){
                return 2;
            }
        }
        if(found == 5)
            return 0;
        (*line)++;
        memset(buffer,0,MAX_BUFFER);
        memset(cleanBuffer, 0, MAX_BUFFER);
    }while(fgets(buffer, MAX_BUFFER, filelink));

    return 3;
}

void printFoundations(Foundations *foundation){
    printf("FOUNDATIONS:\n");
    for(int i = 0; i < 4; i++){
        printf("%c%c ", foundation->foundation[i].rank, foundation->foundation[i].suit);
    }
    printf("\n");
}