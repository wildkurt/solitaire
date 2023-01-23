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
    Rules rules;
    Foundation foundation;
    Tableau tableau;
    StockWaste stockWaste;
    Moves moves;
    long int configID;
public:
    gameConfiguration();
    void setRuleCardTurn(bool c);
    void setRuleResetLimit(bool c);
    void setRuleResetNumber(int n);
    void addCardToFoundation(Card c);
    void addCardToTableau(int col, Card c);
    void addCardToStockWaste(Card c);
    void addMoveToMoves(Move m);
    void getRules();
    void getFoundation();
    void getTableau();
    void getStock();
    void getMoves();
    void getGameId();
};


#endif //SOLITAIRE_GAMECONFIGURATION_H
