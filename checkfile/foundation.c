//
// Created by wende on 5/30/2022.
//

#include <stdio.h>
#include <string.h>
#include "foundation.h"
#include "check.h"

/** This just gets the foundations and makes sure the suits are in the right order.
 * There is a function to print the foundations for testing purposes for check,
 * put can be used in other executables like advance.*/

int findFoundations(char *buffer, FILE *input, int *line){
    int index = 0;
    do{
        *line = *line + 1;
        if(strstr(buffer, "TABLEAU:") != 0){
            fputs(buffer, input);
            break;
        }
        for(int i = 0; buffer[i] != '\0' || i < MAX_BUFFER; i++){
            if(buffer[i] == '#')
                break;
            if((buffer[i] == '_' || isRank(buffer[i])) && isSuit(buffer[i + 1])){
                fd[index].rank = buffer[i];
                fd[index].suit = buffer[i+1];
                fd[index].covered = 'F';
                index++;
            }
        }
        memset(buffer, 0, MAX_BUFFER);
    }while(fgets(buffer,MAX_BUFFER, input) != 0);
    if(fd[0].suit == 'c' && fd[1].suit == 'd' && fd[2].suit == 'h' && fd[3].suit == 's')
        return 1;
    else
        return 0;
}

void printFoundation(){
    for(int i = 0; i < 4; i++){
        printf("%c%c ", fd[i].rank, fd[i].suit);
    }
    printf("\n");
}