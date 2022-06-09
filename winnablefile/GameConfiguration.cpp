//
// Created by wende on 6/7/2022.
//

#include "GameConfiguration.h"

#include <utility>

GameConfiguration::GameConfiguration(std::string inputfilename) {
    this->inputfilename = std::move(inputfilename);
    rules = rules.findRules(this->inputfilename);
    foundation = foundation.getFoundation(this->inputfilename);
    tableau = tableau.getTableau(this->inputfilename);
    stock = stock.getStock(this->inputfilename);
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
