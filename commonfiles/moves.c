//
// Created by wendellbest on 11/23/23.
//

#include <stdio.h>
#include <string.h>
#include "moves.h"

int getMovesFromFile(char *inputfilename, Moves *moves){
    /*Assuming that the file is correct up until the MOVES: section.
     * Need to find where the moves begin, then need to start reading in the moves and make sure the format is correct.
     * Incorrect Format:
     * Using characters other than '.', 'r', 'w', '-', '>', 'f', or '1-7'
     * Spaces - either not where they belong or where they don't be long. "w->f" should not have any spaces.
     * Invalid Moves:
     * When a card can't be moved from one spot to another. When there isn't anymore stock cards. When the maximum
     * number of waste resets have been reached.*/
    FILE *inputFile;
    char buffer[MAX_BUFFER] = {0}, trimBuffer[MAX_BUFFER]={0};
    int line = 0, movesIndex = 0;

    inputFile = fopen(inputfilename, "r");

    if(!inputFile){
        fprintf(stderr, "Unable to open %s\n", inputfilename);
        return 0;
    }

    while(fgets(buffer, MAX_BUFFER, inputFile)){
        int index =0;

        line++;

        for(int i = 0; i < MAX_BUFFER || buffer[i] != '\0' || buffer[i] != '#'; i++)
            trimBuffer[index++] = buffer[i];
        if(strstr(trimBuffer, "MOVES:") ==0)
            break;
    }
    //Assuming that there are no moves on the same line as MOVES:
    while(fgets(buffer, MAX_BUFFER, inputFile)){
        int index = 0;
        line++;
        for(int i = 0; i < MAX_BUFFER || buffer[i] != '\0' || buffer[i] != '#'; i++){
            trimBuffer[index++] = buffer[i];
        }
        for(int i = 0; trimBuffer[i] != '\0'; i++){
            if(validMoveFrom(trimBuffer[i]) && trimBuffer[i+1] == '-' && trimBuffer[i+2] == '>' && validMoveTo(trimBuffer[i+3])){
                Move tempMove = {trimBuffer[i], trimBuffer[i+3], 0};
                moves->moves[movesIndex++] = tempMove;
                i+=2;
            }
            else if(validAction(trimBuffer[i])){
                Move tempMove = {0, 0, trimBuffer[i]};
                moves->moves[movesIndex++] = tempMove;
            }
            else if(trimBuffer[i] == ' ')
                continue;
            else{
                fprintf(stderr, "Improper format for move at line %d column %d\n", line, index);
                return 0;
            }
        }
        memset(buffer, 0, MAX_BUFFER);
        memset(trimBuffer, 0, MAX_BUFFER);
    };
}
void addMoveToMoves(Move move, Moves *moves){}
void printMoves(Moves *moves){}
int validMoveFrom(char c){
    char *fromMoves = "w1234567";

    if(strchr(fromMoves, c) == 0)
        return 1;
    else
        return 0;
}
int validMoveTo(char c){
    char *toMoves = "1234567f";

    if(strchr(toMoves, c)==0)
        return 1;
    else
        return 0;
}
int validAction(char c){
    char *actions ="r.";

    if(strchr(actions, c) == 0)
        return 1;
    else
        return 0;
}