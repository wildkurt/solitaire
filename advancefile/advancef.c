//
// Created by wendellbest on 10/9/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "advance.h"
#include "../checkfile/check.h"

void getCommandLineFlags(int args, char **argv, GameFlags *gameflags){

    for(int i = 1; i < args; i++){
        if(strcmp(argv[i], "-m") == 0){
            gameflags->moves = 't';
            gameflags->numberMoves = atoi(argv[i+1]);
        }
        else if(strcmp(argv[i],"-o") == 0){
            gameflags->outputfile = 't';
            gameflags->outputfileName = malloc(sizeof(argv[i+1]));
            strcpy(gameflags->outputfileName, argv[i+1]);
        }
        else if(strcmp(argv[i], "-x") == 0){
            gameflags->exchange = 't';
        }
        else if(strcmp(argv[i-1],"-o") != 0 && strcmp(argv[i-1],"-m") != 0){
            gameflags->inputFile = malloc(sizeof(argv[i]));
            strcpy(gameflags->inputFile, argv[i]);
        }
    }
}

int checkFile(char *filename){
    FILE *outputToCheck;
    char *check = "./check ", *command, *validFile = "Input file is valid\n", buffer[MAX_BUFFER]={0};
    int length = 0;

    length = strlen(filename) + strlen(check) + 1;
    command = malloc(length * sizeof(char));
    strcat(command, check);
    strcat(command, filename);

    outputToCheck = popen(command, "r");
    fgets(buffer, MAX_BUFFER, outputToCheck);
    if(strcmp(buffer, validFile) == 0)
        return 0;
    else{
        fprintf(stderr, "%s\n", buffer);
        return 1;
    }
}