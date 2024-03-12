//
// Created by wendellbest on 3/5/24.
//

#ifndef SOLITAIRE_WINNABLE_H
#define SOLITAIRE_WINNABLE_H

#include <string>
#include "../commonfiles/gameconfiguration.h"
#include "../movefiles/moves.h"

class Winnable{
private:
    bool limitmoves;
    int movestoplay;
    bool useHashTable;
    bool foundationSafeMoves;
    bool verboseMode;
    std::string inputfile;
    GameConfiguration game;
    Move winningList[1000];
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
    bool checkForWinningCondition(std::string inputfile);
    int getNumberFromString(std::string result);
    void addValidMoveToWinningList(int index, Move move);
    bool searchForWinningSeriesOfMoves(int *movesSoFar);
};
#endif //SOLITAIRE_WINNABLE_H
