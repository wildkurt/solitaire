//
// Created by wendellbest on 2/14/24.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "advance.h"

void getCommandLineArguments(int args,char **argv, AdvanceArgs *arguments){
    for(int i = 1; i < args; i++){
        if(strstr(argv[i],"-m")!=0){
            arguments->movesLimit = 't';
            arguments->numberToPlay = atoi(argv[i+1]);
            i+=2;
        }
        else if(strstr(argv[i],"-o")!=0){
            int length = (int)strlen(argv[i+1]);
            arguments->outputfile = malloc((length + 1) * sizeof(char));
            strcpy(arguments->outputfile, argv[i+1]);
            arguments->outputToFile = 't';
            i+=1;
        }
        else if(strstr(argv[i], "-x")!=0){
            arguments->exchangeFormat = 't';
        }
        else{
            int length = (int)strlen(argv[i]);
            arguments->inputfile = malloc((length + 1) * sizeof(char));
            strcpy(arguments->inputfile, argv[i]);
        }
    }
}
/**In this function, the scenario is that a input file name was not provided. The issue this causes is that if a file
 * is provided by STDIN stream to Advance then CHECK will end up consuming the stream buffer which means Advance won't
 * have access to the game file. The solution is to write the raw data to a file and then pass the name of that file to
 * CHECK so it can perform its function.*/
void writeSTDINtoFile(AdvanceArgs *arguments){
    char *advanceInputFile = "advanceInputFile.txt";
    FILE *advanceFile = fopen(advanceInputFile,"w");
    char buffer[MAX_BUFFER] = {0};

    //Give the file name to arguments
    arguments->inputfile = advanceInputFile;

    //Copy stdin to a file
    while(fgets(buffer, MAX_BUFFER, stdin )){
        fputs(buffer, advanceFile);
        memset(buffer, 0, MAX_BUFFER);
    }

    fclose(advanceFile);
}

int checkGameFile(AdvanceArgs *arguments){
    char checkcommand[MAX_BUFFER] ={0};
    char buffer[MAX_BUFFER] = {0};
    strcat(checkcommand, "./check ");
    strcat(checkcommand, arguments->inputfile);
    FILE *runCheck;

    runCheck = popen(checkcommand,"r");
    while(fgets(buffer, MAX_BUFFER, runCheck)){
        if(strstr(buffer,"Input file is valid\n") != 0)
            return 0;
        memset(buffer, 0, MAX_BUFFER);
    }
    return 1;
}

void getTheGameConfiguration(AdvanceArgs *arguments, GameConfiguration *game, Moves *moveList){
    char buffer[MAX_BUFFER] = {0};
    int line = 0;
    FILE *inputFile;

    inputFile = fopen(arguments->inputfile, "r");

    getRules(&game->rules, &line, inputFile, buffer);
    getFoundations(&game->foundation, &line, inputFile, buffer);
    getTableau(&game->tableau, &line, inputFile, buffer);
    getStockWaste(&game->stockwaste, &line, inputFile, buffer);
    if(getMoves(moveList->moves, inputFile, buffer)){
        exit(1);
    }
    fclose(inputFile);
}
/**Legal moves:
 * Waste to any column or foundation
 * column to any column and foundation
 * Turn over cards if there are any to turn over in the stock.
 * Reset the waste to stock if there are resets remaining and cards in the waste pile
 *
 * FOUNDATIONS: card needs to be one rank higher and same suit as one of the foundation cards.
 * TABLEAU: can move one or more cards from one column to another, but the destination card must be one rank higher and
 * a different color from the source column
 * STOCK: Can turn over one or three cards. Can online reset if there are remaining resets. the visible card is the top
 * card in the waste.
 * */
int checkTheGameMoves(AdvanceArgs *arguments, GameConfiguration *game, Moves *movesList, int *moves){
    int remainingWastResets = 0;
    char *columns = "1234567";

    for(int i = 0; movesList->moves[i].from != 0 || movesList->moves[i].actionn != 0; i++){
        //In the event that the moves are limited to a certain number, the processing of moves will stop even if more remain
        if(arguments->movesLimit == 't' && arguments->numberToPlay == *moves){
            return 0;
        }
        (*moves)++;
        //'w' can be a destination and 'f' can't be a source.
        if(movesList->moves[i].from == 'f' || movesList->moves[i].to == 'w'){
            fprintf(stderr,"Move %d is illegal: %c->%c\n", *moves, movesList->moves[i].from, movesList->moves[i].to);
            return 1;
        }
        //Moving from waste
        if(movesList->moves[i].from == 'w'){
            // move to foundations
            if(movesList->moves[i].to == 'f'){
                Card source;
                getTopWasteCard(&game->stockwaste, &source);
                if(addCardToFoundations(&game->foundation, source)){
                    fprintf(stderr, "Move %d is illegal: %c->%c\n", *moves, movesList->moves[i].from, movesList->moves[i].to);
                    return 1;
                }
                removeCardFromWaste(&game->stockwaste, &game->rules, &source);
            }
            else{
                Card destination, source;
                getTopTableauColumnCard(&game->tableau, movesList->moves[i].to, &destination);
                getTopWasteCard(&game->stockwaste, &source);
                if(!isSameColor(destination.suit, source.suit) && isRank(destination.rank) - 1 == isRank(source.rank)){
                    removeCardFromWaste(&game->stockwaste, &game->rules, &source);
                    addCardToTableauColumn(&game->tableau, movesList->moves[i].to, &source);
                }
                else if(source.rank == 'K' && destination.rank == 0){
                    removeCardFromWaste(&game->stockwaste, &game->rules, &source);
                    addCardToTableauColumn(&game->tableau, movesList->moves[i].to, &source);
                }
                else{
                    fprintf(stderr, "Move %d is illegal: %c->%c\n", *moves, movesList->moves[i].from, movesList->moves[i].to);
                    return 1;
                }
            }
            continue;
        }
        else if(strchr(columns, movesList->moves[i].from) && strchr(columns, movesList->moves[i].to) && movesList->moves[i].from != 0){
            if(!moveCardFromColumnToColumn(&game->tableau, movesList->moves[i].from, movesList->moves[i].to)){
                fprintf(stderr,"Move %d is illegal: %c->%c\n", *moves, movesList->moves[i].from, movesList->moves[i].to);
                return 1;
            }
            continue;
        }
        else if(strchr(columns, movesList->moves[i].from) && movesList->moves[i].to == 'f'){
            Card source;
            getTopTableauColumnCard(&game->tableau, movesList->moves[i].from, &source);
            if(addCardToFoundations(&game->foundation, source)){
                fprintf(stderr, "Move %d is illegal: %c->%c\n",*moves, movesList->moves[i].from, movesList->moves[i].to);
                return 1;
            }
            removeCardFromColumn(&game->tableau, movesList->moves[i].from, source);
            continue;
        }
        //turn over cards in stock
        if(movesList->moves[i].actionn == '.'){
            if(doStockWasteCardTurnover(&game->stockwaste, &game->rules)){
                fprintf(stderr,"Move %d is illegal: %c\n", *moves, movesList->moves[i].actionn);
                return 1;
            }
            continue;
        }
        //reset the waste back to stock
        if(movesList->moves[i].actionn == 'r'){
            if(remainingWastResets == game->rules.wasteResets){
                fprintf(stderr,"Move %d is illegal: %c\n", *moves, movesList->moves[i].actionn);
                return 1;
            }
            if(resetWasteToStock(&game->stockwaste)){
                remainingWastResets++;
            }
            else{
                fprintf(stderr,"Move %d is illegal: %c\n", *moves, movesList->moves[i].actionn);
                return 1;
            }
        }
    }
    return 0;
}

void printGameInExchangeFormat(GameConfiguration game){
    printRules(&game.rules);
    printFoundations(&game.foundation);
    printTableau(&game.tableau);
    printStockWaste(&game.stockwaste);
    printf("MOVES:\n");
}

void printGameInHumanReadable(GameConfiguration game){
    printFoundations(&game.foundation);
    printf("TABLEAU:\n");
    printHumanReadTableau(&game.tableau);
    printf("Waste top\n");
    printfHumanReadTopWaste(&game.stockwaste);
}

void printGameConfigurationnToFile(GameConfiguration game, AdvanceArgs arguments){
    FILE *outputtofile;

    outputtofile = fopen(arguments.outputfile,"w");
    printRulesToFile(outputtofile, &game.rules);
    printFoundationToFile(outputtofile, &game.foundation);
    printTableauToFile(outputtofile,&game.tableau);
    printStockWasteToFile(outputtofile, &game.stockwaste);
    fprintf(outputtofile,"MOVES:\n");
    fclose(outputtofile);
}