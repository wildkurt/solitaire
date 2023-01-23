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
    configID = 0;
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

void gameConfiguration::getRules() {
    std::cout << "Turn over 3 cards is: " << rules.getTurn3Cards() << std::endl;
    std::cout << "Reset limit is: " << rules.getResetsLimited() << std::endl;
    std::cout << "Reset number is: " << rules.getResetLimit() << std::endl;
}

void gameConfiguration::getFoundation() {
    foundation.printFoundations();
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

void gameConfiguration::getGameId() {
    configID = this->moves.buildGameConfigNumber();
}


