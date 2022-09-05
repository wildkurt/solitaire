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

gameBoard::gameBoard(const gameBoard &old) {
    this->tableau = old.tableau;
    this->stock = old.stock;
    this->foundations = old.foundations;
    this->rules = old.rules;
    this->movesList = old.movesList;
}

gameBoard &gameBoard::operator=(const gameBoard &old) {
    this->tableau = old.tableau;
    this->stock = old.stock;
    this->foundations = old.foundations;
    this->rules = old.rules;
    this->movesList = old.movesList;
    return *this;
}

void gameBoard::printGameBoard() {
    rules.printRules();
    foundations.printFoundation();
    tableau.printTableau();
    stock.printStock();
}

bool gameBoard::gameInWinningConfig() {
    bool result = true;
    if(tableau.winningConfigTableau()){
       result =  false;
    }
    if(stock.winningConfigStock()){
        result = false;
    }
    return result;
}

void gameBoard::addMove(char from, char to) {
    movesList.emplace_back(from,to);
}

void gameBoard::removeMove() {
    movesList.pop_back();
}

