//
// Created by wende on 6/7/2022.
//

#include "GameConfiguration.h"

#include <utility>

GameConfiguration::GameConfiguration() {
    inputfilename = nullptr;
    winningGameConfiguration = false;
}

GameConfiguration::GameConfiguration(std::string inputfilename) {
    this->inputfilename = std::move(inputfilename);
    rules = rules.findRules(this->inputfilename);
    foundation = foundation.getFoundation(this->inputfilename);
    tableau = tableau.getTableau(this->inputfilename);
    stock = stock.getStock(this->inputfilename);
    winningGameConfiguration = false;
}

GameConfiguration::GameConfiguration(const GameConfiguration &game) {
    this->inputfilename = game.inputfilename;
    this->foundation = game.foundation;
    this->rules = game.rules;
    this->tableau = game.tableau;
    this->stock = game.stock;
    this->winningGameConfiguration = game.winningGameConfiguration;
}

GameConfiguration &GameConfiguration::operator=(const GameConfiguration &game) {
    this->inputfilename = game.inputfilename;
    this->foundation = game.foundation;
    this->rules = game.rules;
    this->tableau = game.tableau;
    this->stock = game.stock;
    this->winningGameConfiguration = game.winningGameConfiguration;

    return *this;
}

int GameConfiguration::getRulesTurn() {
    return rules.getTurn();
}

int GameConfiguration::getRulesLimit() {
    return rules.getLimit();
}

bool GameConfiguration::isGameFoundationFilled() {
    return foundation.isFoundationFilled();
}

void GameConfiguration::printGameFoundation() {
    foundation.printFoundation();
}

void GameConfiguration::printGameTableau() {
    tableau.printTableau();
}

void GameConfiguration::printGameStock() {
    stock.printStock();
}

bool GameConfiguration::isGameWinnable() {
    bool result = false;
    if(!tableau.anyCoveredCards() && stock.isStockEmptyAndOneWasteCard())
        result = true;
    return result;
}

void GameConfiguration::addMove(Moves move) {
    moves.push_back(move);
}
