//
// Created by wendellbest on 3/8/22.
//

#ifndef SOLITAIRE_ADVANCE_H
#define SOLITAIRE_ADVANCE_H

#define MAX_SIZE 100
#include "../checkfile/check.h"
#include "../checkfile/card.h"
typedef struct gameConfig{
    char limitOnMoves; //from command line
    int moves; //from command line
    int totalMoves;
    char printToFile; //from command line
    char printToExchange; //from command line
    char turnOverThree; //From file
    char limitedGame; //from file
    int wasteResetsAllowed; //from file, sets how many resets are allowed
    char *outputFile; //from command line
}gameConfig;

Card foundations[4];
Card t7[30];
Card t6[30];
Card t5[30];
Card t4[30];
Card t3[30];
Card t2[30];
Card t1[30];
Card sw[30];

void processMoves(char *buffer, FILE *input, gameConfig *gameFile);
void writeToFile(gameConfig *);
void writeToExchange(gameConfig *);
void writeHumanReadable(gameConfig *);
void printCardArray(Card *);
#endif //SOLITAIRE_ADVANCE_H
