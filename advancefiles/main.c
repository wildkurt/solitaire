//
// Created by wendellbest on 2/14/24.
//

/**Will use check to confirm file format is correct. Will need to read from a file or stdin.
 * There are three command line switches:
 * "-m N" which specifies how many moves will be played from the file, default is all movies.
 * "-o file" specifies an output file for the game configuration after the moves have been made.
 * "-x" indicates the output format to stdout, exchange or human readable
 * The moves will be subject to the rules of solitaire.
 * Symbols:
 * "w" for the waste stack
 * "1-7" for the columns
 * "f" for the foundations
 * "->" between two symbols indicates from and to
 * "." turn over T cards (according to the RULES:)
 * "r" reset the waste
 * MOVES: will need to be checked for correct format and also validity of the move.*/
#include <stdio.h>
#include <stdlib.h>
#include "advance.h"

int main(int args, char *argv[]){
    int moves = 0;
    AdvanceArgs arguments = {0,0,0,0,0,0};

    //Get the command line arguments if any, maybe reading from stdin
    getCommandLineArguments(args,argv, &arguments);

    if(arguments.inputfile == 0){
        writeSTDINtoFile(&arguments);
    }
    printf("Processed %d moves, all valid\n",moves);
}