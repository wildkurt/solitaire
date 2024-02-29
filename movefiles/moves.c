//
// Created by wendellbest on 2/5/24.
//
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "moves.h"

char *validMoveChar = "w1234567f";

int getMoves(Move *moves, FILE *inputfile, char *buffer){
    int movesIndex = 0;

    while(fgets(buffer, MAX_BUFFER, inputfile)){
        for(int i = 0; i < MAX_BUFFER && buffer[i] != '#' && buffer[i] != '\n'; i++){
            if(strchr(validMoveChar, buffer[i]) && buffer[i+1] == '-' && buffer[i+2] == '>' && strchr(validMoveChar, buffer[i+3])){
                moves[movesIndex].from = buffer[i];
                moves[movesIndex++].to = buffer[i+3];
            }
            else if(buffer[i] == '.' || buffer[i] == 'r'){
                moves[movesIndex++].actionn = buffer[i];
            }
        }
        memset(buffer, 0, MAX_BUFFER);
    }
    return 0;
}

void printMoves(Moves *moves){
    for(int i = 0; moves->moves[i].from != 0 || moves->moves[i].actionn != 0;i++){
        if(moves->moves[i].from != 0)
            printf("%c->%c \n", moves->moves[i].from, moves->moves[i].to);
        if(moves->moves[i].actionn != 0)
            printf("%c\n", moves->moves[i].actionn);
    }
}