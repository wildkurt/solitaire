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
public:
    Winnable();
    Winnable(const Winnable &w);
    Winnable& operator=(const Winnable& w );
    void retrieveCommandLineArguments(int args,char **argv);
    bool getGameFile(std::string filename);
    bool checkGameFile(std::string filename);
    std::string getGameInputfile(){return this->inputfile;}
    int getMovesToPlay(){return this->movestoplay;}
    void printWinnableCLIArguments();
    void printGameConfiguration();

    bool isGameWinnable(Move pMove[1000], int validMoves, int *numberOfConfigurations);
    void printGameToFile(std::string filename);

    void appendMoveToFile(char i, char j, char k);

    bool isMoveValid(std::string outputfilename);

    bool gameIsInGauranteedWinCondition();
};
#endif //SOLITAIRE_WINNABLE_H
