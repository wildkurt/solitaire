//
// Created by wendellbest on 3/18/23.
//

#include <iostream>
#include <fstream>
#include "gameConfiguration.h"
GameConfiguration &GameConfiguration::operator=(const GameConfiguration &ngame) {
    this->rules = ngame.rules;
    this->foundations = ngame.foundations;
    this->tableau = ngame.tableau;
    this->stockWaste = ngame.stockWaste;
    this->moves = ngame.moves;
    this->currentMove = ngame.currentMove;
    return *this;
}
void GameConfiguration::printRules(std::ofstream *file) {
    *file << "RULES:" << std::endl;
    if(getRuleCardTurnover())
        *file << " turn 3" << std::endl;
    else
        *file << " turn 1" << std::endl;
    if(getRuleLimitedWasteResets())
        *file << " limit " << getRuleNumberofWasteResets() << std::endl;
    else
        *file << " unlimited" << std::endl;
}

void GameConfiguration::addCardToFoundations(int b,Card c) {
    foundations.addCard(b,c);
}


