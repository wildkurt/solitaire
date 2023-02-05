//
// Created by wendellbest on 1/15/23.
//

#ifndef SOLITAIRE_GAMECONFIGURATION_H
#define SOLITAIRE_GAMECONFIGURATION_H


#include "tableau.h"
#include "rules.h"
#include "foundation.h"
#include "StockWaste.h"
#include "Moves.h"

class gameConfiguration{
private:
    Foundation foundation;
    Tableau tableau;
    StockWaste stockWaste;
    Moves moves;
    long int movesSoFar;
    long int configID;
public:
    Rules rules;
    gameConfiguration();
    gameConfiguration(const gameConfiguration& gameb);
    gameConfiguration& operator=(const gameConfiguration& gameb);
    ~gameConfiguration()= default;
    void setRuleCardTurn(bool c);
    void setRuleResetLimit(bool c);
    void setRuleResetNumber(int n);
    void setGameId();
    void addCardToFoundation(Card c);
    void addCardToTableau(int col, Card c);
    void addCardToStockWaste(Card c);
    void addMoveToMoves(Move m);
    void getRules();
    void getFoundation();
    void getTableau();
    void getStock();
    void getMoves();
    long int getGameId();
    void incrementMovesSoFar(){movesSoFar++;}
    long int getMovesSoFar(){return movesSoFar;}
};


#endif //SOLITAIRE_GAMECONFIGURATION_H
