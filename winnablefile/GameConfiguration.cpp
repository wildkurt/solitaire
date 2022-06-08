//
// Created by wende on 6/7/2022.
//

#include "GameConfiguration.h"

#include <utility>

GameConfiguration::GameConfiguration(std::string inputfilename) {
    this->inputfilename = std::move(inputfilename);
    rules = rules.findRules(this->inputfilename);
    foundation = foundation.getFoundation(this->inputfilename);
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
