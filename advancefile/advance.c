//
// Created by wendellbest on 5/31/22.
//

#include "advance.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "../checkfile/check.h"
#include "../checkfile/tableau.h"
#include "../checkfile/foundation.h"
#include "../checkfile/stockWaste.h"
#include "moves.h"
#include "printGame.h"
#include "printGameToFile.h"

int main(int args, char *argv[]){
    GameConfiguration gameconfiguration ={'F', -1, 'F', 0, 'F'};
    FILE *input;
    char *check = "./cmake-build-debug/check", *lim;
    char *inputFileName = 0;
    int line = 0, movess = 0;
    char buffer[MAX_BUFFER] = {0};
    char nNumber[MAX_BUFFER] = {0};
    char outPutFile[MAX_BUFFER] = {0};
    char fileName[MAX_BUFFER] = {0};
    char letter;
    Rules rules;

    //Input from stdin that handles any flags
    if(args < 2){
        int i = 0;
        while(1){
            letter = getchar();
            if(letter == '\n')
                break;
            else
                buffer[i++] = letter;
        }
        //got the line from stdin in buffer, now to get flags if any
        for(int i = 0; i < strlen(buffer); i++){
            if(buffer[i] == '-'){
                if(buffer[i+1] == 'm'){
                    gameconfiguration.limitNumMoves = 'T';
                    i+=3;
                    int j = 0;
                    while(isdigit(buffer[i])){
                        nNumber[j++] = buffer[i++];
                    }
                    gameconfiguration.numberMovesToPlay = strtol(nNumber,0,0);
                }
                else if(buffer[i+1] == 'o'){
                   gameconfiguration.writeToFile = 'T';
                   i+=3;
                   int j = 0;
                   while(isalnum(buffer[i]) || ispunct(buffer[i])){
                        outPutFile[j++] = buffer[i++];
                   }
                    gameconfiguration.filename = calloc(strlen(outPutFile) + 1, sizeof(char));
                    gameconfiguration.filename = strcpy(gameconfiguration.filename, outPutFile);
                }
                else if(buffer[i+1] == 'x'){
                    gameconfiguration.exchangeFormat = 'T';
                    i+=2;
                }
            }
            else{
                int j = 0;
                while(isalnum(buffer[i]) || ispunct(buffer[i])){
                    fileName[j++] = buffer[i++];
                }
                gameconfiguration.filename = calloc(strlen(fileName)+1, sizeof(char));
                gameconfiguration.filename = strcpy(gameconfiguration.filename, fileName);
            }
        }

    }
    //flags from command line
    else {
        for (int i = 1; i < args; i++) {
            //Switch "-m N" indicates at most N moves should be played from input file
            if (strcmp(argv[i], "-m") == 0) {
                gameconfiguration.limitNumMoves = 'T';
                gameconfiguration.numberMovesToPlay = (long) strtol(argv[i + 1], 0, 0);
                i += 2;
            }
            //Switch "-o file" indicates game configuration output to a file
            if (strcmp(argv[i], "-o") == 0) {
                gameconfiguration.writeToFile = 'T';
                gameconfiguration.filename = calloc(strlen(argv[i + 1]), sizeof(char));
                gameconfiguration.filename = strcpy(gameconfiguration.filename, argv[i + 1]);
                i += 2;
            }
            //Switch "-x" game in exchange format
            if (strcmp(argv[i], "-x") == 0) {
                gameconfiguration.exchangeFormat = 'T';
            } else if (strstr(argv[i], "advance") == 0) {
                inputFileName = calloc(strlen(argv[i]) + 1, sizeof(char));
                inputFileName = strcpy(inputFileName, argv[i]);
                gameconfiguration.filename = inputFileName;
            }
        }
    }
    printf("%s\n",gameconfiguration.filename);
    if(gameconfiguration.filename != (void *)0){
        input = fopen(gameconfiguration.filename,"r");
        if(input == (void *)0){
            fprintf(stderr, "Unable to open %s\n", inputFileName);
            return 1;
        }
        unsigned long checkSize = strlen(check);
        unsigned long fileNameSize = strlen(gameconfiguration.filename);
        char *argument = malloc((checkSize + fileNameSize +2) * sizeof(char));
        argument = strcat(argument, check);
        argument = strcat(argument, " ");
        argument = strcat(argument, gameconfiguration.filename);
        if(system(argument)){
            return 1;
        }
    }

    while(fgets(buffer, MAX_BUFFER, input) != 0){
        line++;
        //Ignore hashes
        if(buffer[0] == '#')
            continue;
        //I made a Rules struct, not necessary for check, but trying to lean forward
        //Checks for Turn 1 or Turn 3
        if(strstr(buffer, "turn 1") != 0){
            rules.turnOver = 1;
        }
        if(strstr(buffer, "turn 3") != 0){
            rules.turnOver = 3;
        }
        //Checks for limit N or unlimited
        if(strstr(buffer, "unlimited") != 0){
            rules.limit = -1;
        }
        //I needed to do this this way so I could use scanf to get the number from the
        //string, and if the number is bigger than one digit.
        lim = strstr(buffer, "limit ");
        if(lim != 0){
            int bob = 0;
            char string[10];
            sscanf(lim,"%s %d", string, &bob);
            rules.limit = bob;
        }
        if(strstr(buffer, "FOUNDATIONS:") != 0){
            //This is where the foundations functions take over
            findFoundations(buffer, input, &line);
        }
        if(strstr(buffer, "TABLEAU:") != 0){
            findTableau(buffer, input, &line);
        }
        if(strstr(buffer, "STOCK:") != 0){
            findStockWaste(buffer, input, &line);
        }
        if(strstr(buffer, "MOVES:") != 0){
            break;
        }
        memset(buffer,0,MAX_BUFFER);
    }
    if(moves(input, &line, &movess, &rules, &gameconfiguration) == 0){
        return 1;
    }
    //printf("Processed %d moves, all valid\n", movess);
    printGame(&rules, &gameconfiguration, &movess);
    if(gameconfiguration.writeToFile == 'T'){
        printGameToFile(&rules, &gameconfiguration);
    }
    return 0;
}