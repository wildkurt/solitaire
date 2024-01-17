//
// Created by wendellbest on 11/22/23.
//

#include <stdlib.h>
#include <string.h>
#include "advance.h"

void getCommandLineFlags(int args, char **argv, GameFlags *gameflags){
    for(int i = 0; i < args; i++){
        //How many moves are to be played
        if(strstr(argv[i], "-m") != NULL){
            gameflags->moves = 't';
            gameflags->numberMoves = atoi(argv[i+1]);
        }
        //Write to an output file instead of STDOUT
        else if(strstr(argv[i], "-o") != NULL){
            gameflags->outputfile = 't';
            gameflags->outputfileName = calloc(strlen(argv[i+1]) + 1, sizeof(char));
            strcpy(gameflags->outputfileName, argv[i+1]);
        }
        //Write game out in exchange format to STDOUT or file
        else if(strstr(argv[i], "-x") != NULL){
            gameflags->exchange = 't';
        }
        //The case that the input file name is the first argument
        else if(i == 0 && (strstr(argv[i],"-") == NULL)){
            gameflags->inputFile = calloc(strlen(argv[i]+1),sizeof(char));
            strcpy(gameflags->inputFile, argv[i]);
        }
        //The case that the file name is not first argument. Must check if the argument is the input file name or the
        //output file name by determining if it is preceded by a "-o" or "-m" since both of these flags have arguments
        else if(i > 0 && (strstr(argv[i-1],"-o") == NULL && strstr(argv[i-1], "-m") == NULL)){
            gameflags->inputFile = calloc(strlen(argv[i]+1),sizeof(char));
            strcpy(gameflags->inputFile, argv[i]);
        }
    }
}
//Always provide a file for check to read from
void writeSTDINtoFile(char *defaultInputFile){
    char buffer[MAX_BUFFER] = {0};
    FILE *adToCh;
    adToCh = fopen(defaultInputFile,"r");
    while(fgets(buffer, MAX_BUFFER, stdin)!=0){
        fputs(buffer, adToCh);
    }
}

int checkFile(char *filename){
    int result = 1;
    char command[MAX_BUFFER] = {0}, buffer[MAX_BUFFER];
    FILE *runCheck;
    //Add string for check
    strcat(command,"./check ");
    //Add filename to command
    strcat(command, filename);
    //Run command and create file descriptor to read check output
    runCheck = popen(command,"r");
    //See if Check reports file is valid. If valid return 0, if not, return 1 and out put the error
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
    char buffer[MAX_BUFFER] = {0}, readBuffer[MAX_BUFFER] = {0};
    int line;
    FILE *inputfile;

    inputfile = fopen(gameflags->inputFile,"r");
    if(inputfile == 0){
        fprintf(stderr, "Unable to find file: %s\n", gameflags->inputFile);
        return 0;
    }
    game->rules.found++;
    findRules(buffer, readBuffer,inputfile, &line, &game->rules);
    findFoundation(buffer, readBuffer,inputfile,&line,&game->foundation);
    findTableau(buffer, readBuffer, inputfile, &line, &game->tableau);
    findStockWaste(buffer, readBuffer, inputfile, &line, &game->stockwaste);
    if(!getMovesFromFile(buffer, readBuffer, inputfile, &line, &game->moves)){
        fprintf(stderr, "Did not find moves in game file line %d\n", line);
        return 0;
    }
    return 1;
}

int checkMoves(GameConfiguration *game){
    //If this function is invoked then there are moves to process
    int moveCounter = 0;
    Move *ptr;
    ptr = game->moves.moves;

    while(ptr->from != 0 || ptr->action !=0){
        //Count the moves
        moveCounter++;
        //check for move or action
        if(ptr->from != 0){
            //Move from waste
            if(ptr->from == 'w'){
                Card *temp = getTopWasteCard(&game->stockwaste);
                //Move to foundation
                if(ptr->to != 'f'){
                    if(addCardToFoundation(temp, &game->foundation)){
                        removeWasteCard(temp);
                    }
                    else{
                        fprintf(stderr,"Move %d is illegal: %c->%c\n",moveCounter, ptr->from, ptr->to);
                        return 0;
                    }
                }
                //Move to columns
                else{
                    //get the top card in the tableau from the indicated column
                    Card *tableauPtr = setPointerToTopCard(ptr->to - '0', &game->tableau);
                    //get the top was card
                    Card *wastePtr = getTopWasteCard(&game->stockwaste);
                    //Compare the cards to see if the waste card can be placed in the column
                    //Waste card must be opposite color and one rank lower
                    if(rankValue(wastePtr->rank) + 1 == rankValue(tableauPtr->rank) && isRedOrBlack(wastePtr->suit) != isRedOrBlack(tableauPtr->suit)){
                        //need to add the waste card to the tableau column
                        *(++tableauPtr) = *wastePtr;
                        removeWasteCard(wastePtr);
                    }
                    else{
                        fprintf(stderr,"Move %d is illegal: %c->%c\n",moveCounter, ptr->from, ptr->to);
                        return 0;
                    }
                }
            }
            //Move from columns
            else{
                //Move to foundtaion
                if(ptr->to == 'f'){
                    //get a pointer to the top card in column
                    Card *tableauPtr = setPointerToTopCard(ptr->from - '0', &game->tableau);
                    if(!addCardToFoundation(tableauPtr, &game->foundation)){
                        fprintf(stderr,"Move %d is illegal: %c->%c\n",moveCounter, ptr->from, ptr->to);
                        return 0;
                    }
                    else{
                        removeCardsFromColumn(tableauPtr);
                    }
                }
                //Move to column
                else{
                    if(!moveColToCol(ptr->from - '0', ptr->to - '0', &game->tableau)){
                        fprintf(stderr,"Move %d is illegal: %c->%c\n",moveCounter, ptr->from, ptr->to);
                        return 0;
                    }
                }
            }

        }
        //Perform action
        else{
            //Reset waste
            if(ptr->action == 'r'){
                if(!doStockWasteReset(&game->stockwaste, &game->rules)){
                    fprintf(stderr,"Move %d is illegal: %c\n", moveCounter, ptr->action);
                    return 0;
                }
            }
            //Turn over card
            if(ptr->action == '.'){
                if(!doStockWasteCardTurnover(&game->rules, &game->stockwaste)){
                    fprintf(stderr,"Move %d is illegal: %c\n", moveCounter, ptr->action);
                    return 0;
                }
            }
        }
    }
    game->moves.totalMoves = moveCounter;
    return 1;
}

void printTheGameToScreen(GameConfiguration *game){
    printf("FOUNDATIONS:\n");
    printFoundation(&game->foundation);
    printf("TABLEAU:\n");
    printTableauGameFormat(&game->tableau);
    printf("Waste top\n");
    Card *temp = getTopWasteCard(&game->stockwaste);
    if(game->moves.totalMoves == 0)
        printf("(empty)\n");
    else
        printf("%c%c\n", temp->rank, temp->suit);
}