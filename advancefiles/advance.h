//
// Created by wendellbest on 11/22/23.
//

#ifndef SOLITAIRE_ADVANCE_H
#define SOLITAIRE_ADVANCE_H

typedef struct GameFlags{
    char moves;
    int numberMoves;
    char outputfile;
    char *outputfileName;
    char exchange;
    char *inputFile;
}GameFlags;

void getCommandLineFlags(int args, char **argv, GameFlags *gameflags);
int checkFile(char *filename);
int readGameFile(GameFlags *gameflags, GameConfiguration *game);

#endif //SOLITAIRE_ADVANCE_H
