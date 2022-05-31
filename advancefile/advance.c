//
// Created by wendellbest on 3/8/22.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "advance.h"
#include "../checkfile/foundation.h"
#include "../checkfile/tableau.h"
#include "../checkfile/stockWaste.h"

int main(int args, char *argv[]){
    gameConfig gameFile = {'n', -1, 0,'n', 'n', 'n', 'n', -1, ""};
    char *filename = NULL;
    FILE *input;
    char *check = "check ";
    char argument[MAX_SIZE]= "";
    char *ptr;
    char c;
    int n;

    for(int i = 0; i < args; i++){
        if(strcmp(argv[i], "-m") == 0){
            i++;
            gameFile.limitOnMoves = 'y';
            gameFile.moves = atoi(argv[i]);
        }
        else if(strcmp(argv[i], "-o")==0){
            gameFile.printToFile = 'y';
            i++;
            gameFile.outputFile = strdup(argv[i]);
        }
        else if(strcmp(argv[i], "-x")==0){
            gameFile.printToExchange = 'y';
        }
        else if(strcmp(argv[i], "./advance")!=0){
            filename = strdup(argv[i]);
        }
    }

    if(filename == NULL){
        input = stdin;
        strcat(argument, check);
        if(system(argument)){
            fprintf(stderr, "File is not valid\n");
            exit(1);
        }
    }
    else{
        strcat(argument, check);
        strcat(argument, filename);
        if(!system(argument)){
            fprintf(stderr, "File is not valid\n");
            exit(1);
        }
        input = fopen(filename, "r");
    }
    char buffer[MAX_SIZE];
    while(fgets(buffer, MAX_SIZE, input)!=0){
        if((ptr=strstr(buffer,"turn"))!=0){
            sscanf(ptr, "%*s %c", &c);
            if(c == '3'){
                gameFile.turnOverThree = 'y';
            }
        }
        if((ptr=strstr(buffer, "limit "))!=0){
            gameFile.limitedGame = 'y';
            sscanf(ptr, "%*s %d", &gameFile.wasteResetsAllowed);
        }
        if(strstr(buffer, "FOUNDATIONS:")!=0){
            findFoundations(buffer, input, &n);
        }
        if(strstr(buffer, "TABLEAU:")!=0){
            findTableau(buffer, input, &n);
        }
        if(strstr(buffer, "STOCK:")!=0){
            findStockWaste(buffer, input, &n);
        }
        if(strstr(buffer, "MOVES:")!=0){
            processMoves(buffer, input, &gameFile);
        }
    }
    rewind(input);
    //printCards(sw,30);
    printf("Processed %d moves, all valid\n", gameFile.totalMoves);
    if(gameFile.printToFile == 'y')
        writeToFile(&gameFile);

    if(gameFile.printToExchange == 'y')
        writeToExchange(&gameFile);
    else
        writeHumanReadable(&gameFile);

    fclose(input);
    return 0;
}
