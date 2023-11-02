//
// Created by wendellbest on 5/31/22.
//

#ifndef SOLITAIRE_ADVANCE_H
#define SOLITAIRE_ADVANCE_H

#include "../checkfile/rules.h"

typedef struct{
    char moves;
    int numberMoves;
    char outputfile;
    char *outputfileName;
    char exchange;
    char *inputFile;
}GameFlags;

typedef struct{
    Rules rules;
}GameConfiguration;

void getCommandLineFlags(int args, char **argv, GameFlags *gameflags);
int checkFile(char *filename);

#endif //SOLITAIRE_ADVANCE_H
