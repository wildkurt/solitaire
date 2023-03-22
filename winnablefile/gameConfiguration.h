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
    bool getRuleCardTurnover(){return rules.getCardTurnover();}
    bool getRuleLimitedWasteResets(){return rules.getLimitedWasteResets();}
    int getRuleNumberofWasteResets(){return rules.getNumberOfWasteResets();}
    void setRuleCardTurnover(bool c){return rules.setCardTurnover(c);}
    void setRuleLimitedWasteResets(bool c){rules.setLimitedWasteResets(c);}
    void setRuleNumberofWasteResets(int c){rules.setNumberOfWasteResets(c);}
    void printRules(std::ofstream *file);
    void addCardToFoundations(int b,Card c);
    void printFoundations(std::ofstream *file){foundations.printFoundations(file);}
    void addCardToTableau(int col, Card c){tableau.addCardToColumn(col,c);}
    void printTableau(std::ofstream *file){tableau.printTableau(file);}
    void addCardToStockWaste(Card c){stockWaste.addCardToSW(c);}
    void printStockWaste(std::ofstream *file){stockWaste.printStockWaste(file);}
    void addMove(Move c){moves.addMove(c);}
    void printMove(std::ofstream *file){currentMove.printMove(file);}
};


#endif //SOLITAIRE_GAMECONFIGURATION_H
