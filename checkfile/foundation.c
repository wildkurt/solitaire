//
// Created by wende on 5/30/2022.
//

#include <stdio.h>
#include <string.h>
#include "foundation.h"

/** This just gets the foundations and makes sure the suits are in the right order.
 * There is a function to print the foundations for testing purposes for check,
 * put can be used in other executables like advance.*/

int findFoundations(char *buffer, FILE *input, int *line, Foundation *foundation){
    int index = 0;
    do{
        *line = *line + 1;
        if(buffer[0] == '\0' || buffer[0] == '#')
            continue;
        if(strstr(buffer, "TABLEAU:") != 0){
            fputs(buffer, input);
            break;
        }
        for(int i = 0; buffer[i] != '\0' || i < MAX_BUFFER; i++){
            if(buffer[i] == '#')
                break;
            if((buffer[i] == '_' || isRank(buffer[i])) && isSuit(buffer[i + 1])){
                foundation->fd[index].rank = buffer[i];
                foundation->fd[index].suit = buffer[i+1];
                foundation->fd[index].covered = 'F';
                index++;
            }
        }
        memset(buffer, 0, MAX_BUFFER);
    }while(fgets(buffer,MAX_BUFFER, input) != 0);
    if( foundation->fd[0].suit == 'c' &&  foundation->fd[1].suit == 'd' &&  foundation->fd[2].suit == 'h' &&  foundation->fd[3].suit == 's')
        return 1;
    else
        return 0;
}

void printFoundation(Foundation *foundation){
    for(int i = 0; i < 4; i++){
        printf("%c%c ",  foundation->fd[i].rank,  foundation->fd[i].suit);
    }
    printf("\n");
}

Card *fdPtr(Foundation *foundation){return  foundation->fd;}

int addCardToFoundation(Card *card, Foundation *foundation){
    for(int i = 0; i < 4; i++){
        if( foundation->fd[i].suit == card->suit && rankValue( foundation->fd[i].rank) + 1 == rankValue(card->rank)){
            foundation->fd[i] = *card;
            return 1;
        }
        else if( foundation->fd[i].rank == '_' && card->rank == 'A' &&  foundation->fd[i].suit == card->suit){
            foundation->fd[i] = *card;
            return 1;
        }
    }
    return 0;
}