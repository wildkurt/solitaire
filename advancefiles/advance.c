//
// Created by wendellbest on 11/22/23.
//

#include <stdlib.h>
#include <string.h>
#include "advance.h"

void getCommandLineFlags(int args, char **argv, GameFlags *gameflags){
    for(int i = 0; i < args; i++){
        if(strstr(argv[i], "-m") != NULL){
            gameflags->moves = 't';
            gameflags->numberMoves = atoi(argv[i+1]);
        }
        else if(strstr(argv[i], "-o") != NULL){
            gameflags->outputfile = 't';
            gameflags->outputfileName = calloc(strlen(argv[i+1]) + 1, sizeof(char));
            strcpy(gameflags->outputfileName, argv[i+1]);
        }
        else if(strstr(argv[i], "-x") != NULL){
            gameflags->exchange = 't';
        }
        else if(i == 0 && (strstr(argv[i],"-") == NULL)){
            gameflags->inputFile = calloc(strlen(argv[i]+1),sizeof(char));
            strcpy(gameflags->inputFile, argv[i]);
        }
        else if(i > 0 && (strstr(argv[i-1],"-o") == NULL && strstr(argv[i-1], "-m") == NULL)){
            gameflags->inputFile = calloc(strlen(argv[i]+1),sizeof(char));
            strcpy(gameflags->inputFile, argv[i]);
        }
    }
}

int checkFile(char *filename){
    int result = 1;
    char command[MAX_BUFFER] = {0}, buffer[MAX_BUFFER];
    FILE *runCheck;

    strcat(command,"./check ");
    strcat(command, filename);

    runCheck = popen(command,"r");
    while(fgets(buffer,MAX_BUFFER, runCheck) != 0){
        if(strcmp(buffer,"Input file is valid\n")==0){
            result = 0;
            break;
        }
        else
            fprintf(stderr, "%s", buffer);
    }
    return result;
}

int readGameFile(GameFlags *gameflags, GameConfiguration *game){
    char buffer[MAX_BUFFER];
    int line;
    FILE *inputfile;

    inputfile = fopen(gameflags->inputFile,"r");
    if(inputfile == 0){
        fprintf(stderr, "Unable to find file: %s\n", gameflags->inputFile);
        return 0;
    }
    game->rules.found++;
    findRules(buffer, inputfile, &line, &game->rules);
    findFoundation(buffer,inputfile,&line,&game->foundation);
    findTableau(buffer, inputfile, &line, &game->tableau);
    findStockWaste(buffer, inputfile, &line, &game->stockwaste);

    return 1;
}