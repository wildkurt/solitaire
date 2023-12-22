//
// Created by wendellbest on 11/22/23.
//

#include <stdlib.h>
#include "advance.h"

void printForDebugging(GameFlags *gameflags, GameConfiguration *game);

int main(int args, char *argv[]){
    GameFlags gameflags = {'f', -1, 'f', 0, 'f', 0};
    GameConfiguration game = {.rules = {0,0,0,0}, .foundation = {0},
                              .tableau = {.t1 = {0}, .t2 = {0}, .t3 = {0}, .t4 = {0}, .t5 = {0}, .t6 = {0}, .t7 = {0}},
                              .stockwaste = {0}, .found =0, .moves={{0,0,0}, .totalMoves = 0},
                              .resetsDone = 0};
    //Command line flags
    getCommandLineFlags(args, argv, &gameflags);
    //There is a given game file
    if(gameflags.inputFile != 0){
        if(checkFile(gameflags.inputFile)){
        exit(1);
        }
    }
    else{
        checkFile("stdin");
    }
    if(!readGameFile(&gameflags, &game)){
        exit(EXIT_FAILURE);
    }
    else
        if(!checkMoves(&game)){
            printTheGameToScreen(&game);
        }
        else{
            printf("Processed %d moves, all valid\n", game.moves.totalMoves);
            printTheGameToScreen(&game);
        }
    return 0;
}

void printForDebugging(GameFlags *gameflags, GameConfiguration *game){
    printf("The game flags are:\n");
    printf("Moves: %c\n", gameflags->moves);
    printf("Number of moves: %d\n", gameflags->numberMoves);
    printf("Outputfile flag: %c\n", gameflags->outputfile);
    printf("Output file name: %s\n", gameflags->outputfileName);
    printf("Exchange format: %c\n", gameflags->exchange);
    printf("Input file name: %s\n", gameflags->inputFile);
    printRulesSTDOUT(&game->rules);
    printFoundation(&game->foundation);
    printTableau(&game->tableau);
    printStockWaste(&game->stockwaste);
    printMoves(&game->moves);
}