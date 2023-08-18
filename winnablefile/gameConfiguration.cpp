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
    this->wasteResets = 0;
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

int GameConfiguration::getCurrentNumberOfMoves() {
    return moves.numberOfMoves();
}

int GameConfiguration::getConfigurationHash() {
    return moves.getHashOfMoves();
}

int GameConfiguration::CanDoSafeMoves() {
    Card arrWasteOrColumns[8];
    Card arrFoundation[4];
    //Check if one or three card turn over
    if(rules.getCardTurnover()){
        tableau.getTopCardValues(arrWasteOrColumns);
        foundations.getCardValues(arrFoundation);
    }
    //For one card turn over
    else{
        tableau.getTopCardValues(arrWasteOrColumns);
        foundations.getCardValues(arrFoundation);
        stockWaste.getWasteValue(arrWasteOrColumns);
    }
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 4; j++){
            //One of the cards in the top column must be one rank higher than card in foundations
            if((arrWasteOrColumns[i].getSuit() == arrFoundation[j].getSuit())&&(arrWasteOrColumns[i].cardRankValueIs() == arrFoundation[j].cardRankValueIs()+1)){
                //c d h s, the value of the foundation card must match the value of the cards of the opposite color
                if(arrWasteOrColumns[i].cardColorIs() == 'r'){
                    if(arrFoundation[j].cardRankValueIs() == arrFoundation[0].cardRankValueIs() && arrFoundation[j].cardRankValueIs() == arrFoundation[3].cardRankValueIs())
                        return i;
                }
                else if(arrWasteOrColumns[i].cardColorIs() == 'b'){
                    if(arrFoundation[j].cardRankValueIs() == arrFoundation[1].cardRankValueIs() && arrFoundation[j].cardRankValueIs() == arrFoundation[2].cardRankValueIs())
                        return i;
                }
            }
        }
    }
    return -1;
}

void GameConfiguration::printStockWast(std::ofstream *pOfstream) {
    stockWaste.printStockWaste(pOfstream);
}

void GameConfiguration::printMoves(std::ofstream *pOfstream) {
    moves.printMoves(*pOfstream);
}
