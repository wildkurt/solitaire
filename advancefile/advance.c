//
// Created by wendellbest on 5/31/22.
//
/**Switches
 * -m N -the max number of moves to play
 * -o file -the file the game configuration needs to be written to
 * -x -the game configuration output will be in exchange format*/
#include <stdio.h>
#include <stdlib.h>
#include "advance.h"
void printForDebugging(GameFlags *gameflags, Rules *rules);

int main(int args, char *argv[]){
    //Get the program flags
    GameFlags gameflags = {'f', -1, 'f', 0, 'f',0};
    GameConfiguration game ={ .rules = {0,0,0,0}, .foundation = {0}};
    getCommandLineFlags(args, argv, &gameflags);
    //Must-read from a file or standard input
    //printForDebugging(&gameflags, &game.rules);
    if(checkFile(gameflags.inputFile)){
        exit(1);
    }
    readGameFile(&gameflags, &game);
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