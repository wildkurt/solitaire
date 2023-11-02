//
// Created by wendellbest on 11/1/23.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../checkfile/check.h"
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
    char *command[MAX_BUFFER] = {0}, buffer[MAX_BUFFER];
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