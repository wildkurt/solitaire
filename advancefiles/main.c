//
// Created by wendellbest on 11/22/23.
//

#include <stdlib.h>
#include "../commonfiles/gameconfiguration.h"
#include "advance.h"

void printForDebugging(GameFlags *gameflags, Rules *rules);

int main(int args, char *argv[]){
    GameFlags gameflags = {'f', -1, 'f', 0};
    GameConfiguration game = {.rules = {0,0,0,0}, .foundation = {0},
                              .tableau = {.t1 = {0}, .t2 = {0}, .t3 = {0}, .t4 = {0}, .t5 = {0}, .t6 = {0}, .t7 = {0}},
                              .stockwaste = {0}, .found =0};
    getCommandLineFlags(args, argv, &gameflags);
    if(checkFile(gameflags.inputFile)){
        exit(1);
    }
    if(!readGameFile(&gameflags, &game)){
        exit(EXIT_FAILURE);
    }
    else
        printForDebugging(&gameflags, &game.rules);
    return 0;
}

void printForDebugging(GameFlags *gameflags, Rules *rules){
    printf("The game flags are:\n");
    printf("Moves: %c\n", gameflags->moves);
    printf("Number of moves: %d\n", gameflags->numberMoves);
    printf("Outputfile flag: %c\n", gameflags->outputfile);
    printf("Output file name: %s\n", gameflags->outputfileName);
    printf("Exchange format: %c\n", gameflags->exchange);
    printf("Input file name: %s\n", gameflags->inputFile);
    printf("Card turn overs: %d\n", rules->turnOver);
    printf("Resets limit: %d\n", rules->limit);
}