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
    std::string outputfile;
    GameConfiguration game;
public:
    Winnable();
    Winnable(const Winnable &w);
    Winnable& operator=(const Winnable& w );
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
    bool searchForWinningSeriesOfMoves(int *movesSoFar, Winnable winnable, Move *winninglist);
    void printListOfWinningMoves(Move pMove[1000]);

    void printGameToExchangeFile();

    bool checkForValidMove();
};
#endif //SOLITAIRE_WINNABLE_H
