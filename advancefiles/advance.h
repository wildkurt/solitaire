//
// Created by wendellbest on 2/14/24.
//

#ifndef SOLITAIRE_ADVANCE_H
#define SOLITAIRE_ADVANCE_H

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
#endif //SOLITAIRE_ADVANCE_H
