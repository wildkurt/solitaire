//
// Created by wende on 5/30/2022.
//

#include <stdio.h>
#include <string.h>
#include "foundation.h"

/** This just gets the foundations and makes sure the suits are in the right order.
 * There is a function to print the foundations for testing purposes for check,
 * put can be used in other executables like advance.*/

int findFoundations(char *buffer, FILE *input, int *line, GameConfiguration *game){
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
                game->foundation.fd[index].rank = buffer[i];
                game->foundation.fd[index].suit = buffer[i+1];
                game->foundation.fd[index].covered = 'F';
                index++;
            }
        }
        memset(buffer, 0, MAX_BUFFER);
    }while(fgets(buffer,MAX_BUFFER, input) != 0);
    if( game->foundation.fd[0].suit == 'c' &&  game->foundation.fd[1].suit == 'd' &&  game->foundation.fd[2].suit == 'h' &&  game->foundation.fd[3].suit == 's')
        return 1;
    else
        return 0;
}

void printFoundation(GameConfiguration *game){
    for(int i = 0; i < 4; i++){
        printf("%c%c ",  game->foundation.fd[i].rank,  game->foundation.fd[i].suit);
    }
    printf("\n");
}

Card *fdPtr(GameConfiguration *game){return  game->foundation.fd;}

int addCardToFoundation(Card *card, GameConfiguration *game){
    for(int i = 0; i < 4; i++){
        if( game->foundation.fd[i].suit == card->suit && rankValue( game->foundation.fd[i].rank) + 1 == rankValue(card->rank)){
            game->foundation.fd[i] = *card;
            return 1;
        }
        else if( game->foundation.fd[i].rank == '_' && card->rank == 'A' &&  game->foundation.fd[i].suit == card->suit){
            game->foundation.fd[i] = *card;
            return 1;
        }
    }
    return 0;
}