//
// Created by wendellbest on 5/31/22.
//

#ifndef SOLITAIRE_ADVANCE_H
#define SOLITAIRE_ADVANCE_H

#include "../checkfile/rules.h"
#include "../checkfile/foundation.h"
#include "../checkfile/check.h"

typedef struct{
    char moves;
    int numberMoves;
    char outputfile;
    char *outputfileName;
    char exchange;
    char *inputFile;
}GameFlags;

void getCommandLineFlags(int args, char **argv, GameFlags *gameflags);
int checkFile(char *filename);
void readGameFile(GameFlags *gameflags, GameConfiguration *game);

#endif //SOLITAIRE_ADVANCE_H
