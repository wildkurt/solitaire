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
void printTheGameFile(GameConfiguration *game);

int main(int args, char *argv[]){
    GameConfiguration game ={ .rules = {0,0,0,0}, .foundation = {0}, .tableau = {.t1 = {0},
                             .t2 = {0}, .t3 = {0}, .t4 = 0, .t5 = {0}, .t6 = {0}, .t7 =  {0}}, .stockwaste = {0},
                              .found = 0, .moves = 0, .resetsDone = 0};
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
        if(game.found == 4)
            fprintf(stderr, "Moves not found at line %d\n", line);
        exit(EXIT_FAILURE);
    }
    //if(game.found == 5)
        //printTheGameFile(&game);
    //Look for missing cards
    if(missingDuplicateCards(&game)){
        return 1;
    }
    return 0;
}

void printTheGameFile(GameConfiguration *game){
    printRulesSTDOUT(&game->rules);
    printFoundation(&game->foundation);
    printTableau(&game->tableau);
    printStockWaste(&game->stockwaste);
}
