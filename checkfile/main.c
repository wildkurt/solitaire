//
// Created by wende on 5/30/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include "../commonfiles/gameconfiguration.h"
#include "check.h"

/** The main program will open the file then parse it to find all
 * the required elements. During parsing, it calls functions that
 * will determine if there is a element present and will also
 * check the tableaus for a legal order. Foundations will be checked
 * for correct suits. It will then initiate a count of covered cards
 * and cards in the stock and waste*/

int main(int args, char *argv[]){
    GameConfiguration game ={ .rules = {0,0,0,0}, .foundation = {0}, .tableau = {.t1 = {0},
                             .t2 = {0}, .t3 = {0}, .t4 = 0, .t5 = {0}, .t6 = {0}, .t7 =  {0}}, .stockwaste = {0}};
    int covered = 0, stock = 0, waste = 0, line = 0;
    //Get the game file name, account for stdin or a file name
    if(args < 2){
        readFile("", &game, &line);
    }
    else{
        readFile(argv[1], &game, &line);
    }
    if(game.found == 5){
        printf( "Input file is valid\n");
        countCards(&covered, &stock, &waste, &game);
        printf("%d covered cards\n", covered);
        printf("%d stock cards\n", stock);
        printf("%d waste cards\n", waste);
        printf("\n");
    }
    else if(game.found < 5){
        if(game.rules.found < 3){
            if(game.rules.found == 2){
                fprintf(stderr,"Waste reset not found %d\n", line);
                exit(EXIT_FAILURE);
            }
            else if(game.rules.found == 1){
                fprintf(stderr, "Card turn over not found line %d\n", line);
                exit(EXIT_FAILURE);
            }
        }
        else{
            switch(game.found){
                case 4 : fprintf(stderr, "Moves not found at line  %d", line); break;
                case 3 : fprintf(stderr, "Stock not found at line  %d", line); break;
                case 2 : fprintf(stderr, "Tableau not found at line  %d", line); break;
                case 1 : fprintf(stderr, "Foundations not found at line  %d", line); break;
                default : fprintf(stderr, "No game configuration found in file\n");
            }
            exit(EXIT_FAILURE);
        }
    }
    //Look for missing cards
    if(missingDuplicateCards(&game)){
        return 1;
    }
    return 0;
}

