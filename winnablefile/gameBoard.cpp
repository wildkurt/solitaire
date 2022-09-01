//
// Created by wendellbest on 7/7/22.
//

#include "gameBoard.h"

/*This code will build the components of the game board which are the
 * rules, foundation, tableau, and stock/waste. */

gameBoard::gameBoard(std::string inputFileName) {
    rules.getRules(inputFileName);
    foundations.getFoundation(inputFileName);
    tableau.getTableau(inputFileName);
    stock.getStock(inputFileName);
}

void gameBoard::printGameBoard() {
    rules.printRules();
    foundations.printFoundation();
    tableau.printTableau();
    stock.printStock();
}
