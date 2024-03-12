//
// Created by wendellbest on 2/14/24.
//

#ifndef SOLITAIRE_ADVANCE_H
#define SOLITAIRE_ADVANCE_H

#include "../commonfiles/gameconfiguration.h"
#include "../movefiles/moves.h"

typedef struct AdvanceArgs{
    char movesLimit;
    int numberToPlay;
    char outputToFile;
    char *outputfile;
    char exchangeFormat;
    char *inputfile;
} AdvanceArgs;

void getCommandLineArguments(int args,char **argv, AdvanceArgs *arguments);
void writeSTDINtoFile(AdvanceArgs *arguments);
int checkGameFile(AdvanceArgs *arguments);
void getTheGameConfiguration(AdvanceArgs *arguments, GameConfiguration *game, Moves *moveList);
int checkTheGameMoves(AdvanceArgs *arguments, GameConfiguration *game, Moves *movesList, int *moves);
void printGameInExchangeFormat(GameConfiguration game);
void printGameInHumanReadable(GameConfiguration game);
void printGameConfigurationnToFile(GameConfiguration game, AdvanceArgs arguments);
#endif //SOLITAIRE_ADVANCE_H
