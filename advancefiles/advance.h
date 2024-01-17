//
// Created by wendellbest on 11/22/23.
//

#ifndef SOLITAIRE_ADVANCE_H
#define SOLITAIRE_ADVANCE_H

#include "../commonfiles/gameconfiguration.h"

typedef struct GameFlags{
    char moves;
    int numberMoves;
    char outputfile;
    char *outputfileName;
    char exchange;
    char *inputFile;
}GameFlags;

void getCommandLineFlags(int args, char **argv, GameFlags *gameflags);
void writeSTDINtoFile(char *defaultInputFile);
int checkFile(char *filename);
int readGameFile(GameFlags *gameflags, GameConfiguration *game);
int checkMoves(GameConfiguration *game);
void printTheGameToScreen(GameConfiguration *game);

#endif //SOLITAIRE_ADVANCE_H
