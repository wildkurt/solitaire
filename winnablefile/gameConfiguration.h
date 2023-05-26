//
// Created by wendellbest on 3/18/23.
//

#ifndef SOLITAIRE_GAMECONFIGURATION_H
#define SOLITAIRE_GAMECONFIGURATION_H


#include "rules.h"
#include "foundations.h"
#include "tableau.h"
#include "stockWaste.h"
#include "moves.h"

class GameConfiguration {
private:
    Rules rules;
    Foundations foundations;
    Tableau tableau;
    StockWaste stockWaste;
    Moves moves;
    Move currentMove;
public:
    GameConfiguration()= default;
    GameConfiguration &operator=(const GameConfiguration &ngame);
    void setRuleCardTurnover(bool c){return rules.setCardTurnover(c);}
    void setRuleLimitedWasteResets(bool c){rules.setResetsLimited(c);}
    void setRuleNumberofWasteResets(int c){rules.setResetLimit(c);}
    void printRules(){rules.printRules();};
    void addCardToFoundations(int b,Card c);
    void printFoundations(){foundations.printFoundations();}
    void addCardToTableau(int col, Card c){tableau.addCardToColumn(col,c);}
    void printTableau(){tableau.printTableau();}
    void addCardToStockWaste(Card c){stockWaste.addCardToSW(c);}
    void printStockWaste(){stockWaste.printStockWaste();}
    void addMove(Move c){moves.addMove(c);}
    void printMove(std::ofstream *file){currentMove.printMove(file);}
};


#endif //SOLITAIRE_GAMECONFIGURATION_H
