//
// Created by wendellbest on 6/9/22.
//

#ifndef SOLITAIRE_WINNABLE_H
#define SOLITAIRE_WINNABLE_H

#include "GameConfiguration.h"
#include "Moves.h"
#include <deque>

class winnable{
private:
    bool limitmoves;
    int numberOfMoves;
    bool hashtanle;
    bool safeMoves;
    bool verboseMode;
    int numberMoveMade;
    char *movesArr;
public:
    winnable()=default;
    winnable(bool limitmoves, int numberOfMoves, bool hashtable, bool safeMoves, bool verboseMode);
    GameConfiguration &findWinningMoves(GameConfiguration &game);
};
#endif //SOLITAIRE_WINNABLE_H
