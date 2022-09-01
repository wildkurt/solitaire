//
// Created by wendellbest on 7/7/22.
//

#ifndef SOLITAIRE_GAMEBOARD_H
#define SOLITAIRE_GAMEBOARD_H
#include <string>
#include "gameRules.h"
#include "gameFoundations.h"
#include "gameTableau.h"
#include "gameStock.h"

/** gameBoard class will essentially contain a complete game*/

class gameBoard {
private:
    gameRules rules;
    gameFoundations foundations;
    gameTableau tableau;
    gameStock stock;
public:
    gameBoard(std::string inputFileName);
    void printGameBoard();
};


#endif //SOLITAIRE_GAMEBOARD_H
