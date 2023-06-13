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

void GameConfiguration::addCardToFoundations(int b,Card c) {
    foundations.addCard(b,c);
}

bool GameConfiguration::gameInWinningConfiguration() {
    if(stockWaste.isSWinWinCond() && !tableau.anyCoveredCards())
        return true;
    else
        return false;
}

bool GameConfiguration::canSafeMovesBeDone() {
    return false;
}
