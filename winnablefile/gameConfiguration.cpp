//
// Created by wendellbest on 1/15/23.
//

#include <iostream>
#include "gameConfiguration.h"

gameConfiguration::gameConfiguration() {
    rules = Rules();
    foundation = Foundation();
    tableau = Tableau();
    stockWaste = StockWaste();
    moves = Moves();
    configID = "";
    movesSoFar = 0;
}

gameConfiguration::gameConfiguration(const gameConfiguration &gameb) {
    rules = gameb.rules;
    foundation = gameb.foundation;
    tableau = gameb.tableau;
    stockWaste = gameb.stockWaste;
    moves = gameb.moves;
    configID = gameb.configID;
    movesSoFar = gameb.movesSoFar;
}

gameConfiguration &gameConfiguration::operator=(const gameConfiguration &gameb) {
    rules = gameb.rules;
    foundation = gameb.foundation;
    tableau = gameb.tableau;
    stockWaste = gameb.stockWaste;
    moves = gameb.moves;
    configID = gameb.configID;
    movesSoFar = gameb.movesSoFar;
    return *this;
}

void gameConfiguration::setRuleCardTurn(bool c) {
    rules.setRuleTurn(c);
}

void gameConfiguration::setRuleResetLimit(bool c) {
    rules.setRuleLimits(c);
}

void gameConfiguration::setRuleResetNumber(int n) {
    rules.setRuleLimitNumber(n);
}

void gameConfiguration::addCardToFoundation(Card c) {
    foundation.addCardToFoundation(c);
}

void gameConfiguration::addCardToTableau(int col,Card c) {
    tableau.addCardToTab(col,c);
}

void gameConfiguration::addCardToStockWaste(Card c) {
    stockWaste.addCardToStockWaste(c);
}

void gameConfiguration::addMoveToMoves(Move m) {
    moves.addMove(m);
}

Rules gameConfiguration::getRules() {
    return rules;
}

Foundation gameConfiguration::getFoundation() {
    return foundation;
}

void gameConfiguration::getTableau() {
    tableau.printTableaus();
}

void gameConfiguration::getStock() {
    stockWaste.printStock();
}

void gameConfiguration::getMoves() {
    moves.printMoves();
}

std::string gameConfiguration::getGameId() {
    return configID;
}

void gameConfiguration::setGameId() {
    configID = this->moves.buildGameConfigNumber();
}

void gameConfiguration::accIncrmntWasteCount() {
    stockWaste.incrementWasteCount();
}

void gameConfiguration::accIncrmntStockCount() {
    stockWaste.incrementStockCount();
}

bool gameConfiguration::accStockInWinning() {
    return stockWaste.isStockWasteInWinningCondition();
}

bool gameConfiguration::accTableauInWinning() {
    return tableau.areColumnCardsCovered();
}






