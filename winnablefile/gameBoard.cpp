//
// Created by wendellbest on 7/7/22.
//

#include "gameBoard.h"

gameBoard::gameBoard(std::string inputFileName) {
    rules.getRules(inputFileName);
    foundations.getFoundation(inputFileName);
    tableau.getTableau(inputFileName);
}
