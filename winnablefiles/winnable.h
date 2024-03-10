//
// Created by wendellbest on 3/5/24.
//

#ifndef SOLITAIRE_WINNABLE_H
#define SOLITAIRE_WINNABLE_H

#include <string>
#include "../commonfiles/gameconfiguration.h"



class Winnable{
private:
    bool limitmoves;
    int movestoplay;
    bool useHashTable;
    bool foundationSafeMoves;
    bool verboseMode;
    std::string inputfile;
    GameConfiguration game;
public:
    Winnable();
    bool getLimitedMoves();
    int getMovestoPlay();
    bool getUseHashTable();
    bool getFoundationSafeMoves();
    bool getVerboseMode();
    std::string getInputFileName();
    void retrieveCommandLineArguments(int args,char **argv);
    bool getAndCheckGameFile();
    void printWinnableCLIArguments();
    void printGameConfiguration();
};
#endif //SOLITAIRE_WINNABLE_H
