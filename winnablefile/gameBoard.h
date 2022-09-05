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
#include "moves.h"

/** gameBoard class will essentially contain a complete game*/

class gameBoard {
private:
    gameRules rules;
    gameFoundations foundations;
    gameTableau tableau;
    gameStock stock;
    std::vector <moves> movesList;
public:
    gameBoard()= default;
    explicit gameBoard(std::string inputFileName);
    gameBoard(const gameBoard &old);
    gameBoard& operator=(const gameBoard &old);
    void printGameBoard();
    bool gameInWinningConfig();
    long numberOfMoves(){return movesList.size();}
    void addMove(char from, char to);
    void removeMove();
};


#endif //SOLITAIRE_GAMEBOARD_H
