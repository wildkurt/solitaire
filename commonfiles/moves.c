//
// Created by wendellbest on 11/23/23.
//

#include <stdio.h>
#include <string.h>
#include "moves.h"

int getMovesFromFile(char * buffer, char *readBuffer, FILE *inputfilename, int *line, Moves *moves){
    /*Assuming that the file is correct up until the MOVES: section.
     * Need to find where the moves begin, then need to start reading in the moves and make sure the format is correct.
     * Incorrect Format:
     * Using characters other than '.', 'r', 'w', '-', '>', 'f', or '1-7'
     * Spaces - either not where they belong or where they don't be long. "w->f" should not have any spaces.
     * Invalid Moves:
     * When a card can't be moved from one spot to another. When there isn't anymore stock cards. When the maximum
     * number of waste resets have been reached.*/

    int movesIndex = 0;
    do{
        memset(readBuffer,0,MAX_BUFFER);
        for(int i = 0; buffer[i] != '\n' && buffer[i] != '\0';i++){
            readBuffer[i] = buffer[i];
        }
        if(strstr(readBuffer, "MOVES:")!=0){
            for(int i = 0; readBuffer[i] != '\0'; i++){
                if(validMoveFrom(readBuffer[i]) && readBuffer[i+1] == '-' && readBuffer[i+2] && validMoveTo(readBuffer[i+3])){
                    moves->moves[movesIndex].from = readBuffer[i];
                    moves->moves[movesIndex].to = readBuffer[i+3];
                    moves->moves[movesIndex].action = 0;
                    movesIndex++;
                }
                else if(validAction(readBuffer[i])){
                    moves->moves[movesIndex].from = 0;
                    moves->moves[movesIndex].to = 0;
                    moves->moves[movesIndex].action = readBuffer[i];
                    movesIndex++;
                }
            }
        }
        else{
            for(int i = 0; readBuffer[i] != '\0'; i++){
                if(validMoveFrom(readBuffer[i]) && readBuffer[i+1] == '-' && readBuffer[i+2] && validMoveTo(readBuffer[i+3])){
                    moves->moves[movesIndex].from = readBuffer[i];
                    moves->moves[movesIndex].to = readBuffer[i+3];
                    moves->moves[movesIndex].action = 0;
                    movesIndex++;
                }
                else if(validAction(readBuffer[i])){
                    moves->moves[movesIndex].from = 0;
                    moves->moves[movesIndex].to = 0;
                    moves->moves[movesIndex].action = readBuffer[i];
                    movesIndex++;
                }
            }
        }
        memset(buffer, 0, MAX_BUFFER);
        (*line)++;
    }while(fgets(buffer,MAX_BUFFER,inputfilename));
    if(movesIndex > 0)
        return 1;
    else
        return 0;
}
void addMoveToMoves(Move move, Moves *moves){}
void printMoves(Moves *moves){
    int i = 0;
    while(moves->moves[i].from != 0 || moves->moves[i].action != 0){
        if(moves->moves[i].from == 0)
            printf("%c", moves->moves[i].action);
        else
            printf("%c->%c", moves->moves[i].from, moves->moves[i].to);
        i++;
        printf(" ");
    }
}
int validMoveFrom(char c){
    char *fromMoves = "w1234567";

    if(strchr(fromMoves, c) == 0)
        return 0;
    else
        return 1;
}
int validMoveTo(char c){
    char *toMoves = "1234567f";

    if(strchr(toMoves, c)==0)
        return 0;
    else
        return 1;
}
int validAction(char c){
    char *actions ="r.";

    if(strchr(actions, c) == 0)
        return 0;
    else
        return 1;
}