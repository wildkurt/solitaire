//
// Created by wendellbest on 1/29/24.
//
#include <stdlib.h>
#include "gameconfiguration.h"

void printTheGameConfiguration(GameConfiguration *game){
    printRules(&game->rules);
    printFoundations(&game->foundation);
    printTableau(&game->tableau);
    printStockWaste(&game->stockwaste);
}

void getTheGameConfigFromFile(GameConfiguration *game, char *inputfile){
    int index = 0;
    FILE *gamefile;
    char buffer[MAX_BUFFER] = {0};

    gamefile = fopen(inputfile,"r");
    if(gamefile == NULL){
        fprintf(stderr, "File %s not found\n", inputfile);
        exit(1);
    }
    getRules(&game->rules, &index, gamefile, buffer);
    getFoundations(&game->foundation, &index, gamefile, buffer);
    getTableau(&game->tableau, &index, gamefile, buffer);
    getStockWaste(&game->stockwaste, &index, gamefile, buffer);
}