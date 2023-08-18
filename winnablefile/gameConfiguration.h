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
    int wasteResets;
public:
    GameConfiguration()= default;
    GameConfiguration &operator=(const GameConfiguration &ngame);
    void setRuleCardTurnover(bool c){return rules.setCardTurnover(c);}
    void setRuleLimitedWasteResets(bool c){rules.setResetsLimited(c);}
    bool getRuleLimitedWasteResets(){return rules.getResetsLimited();}
    int getRuleLimitedWasteNumber(){return rules.getResetLimit();}
    void setRuleNumberofWasteResets(int c){rules.setResetLimit(c);}
    void printRules(){rules.printRules();}
    void printRules(std::ofstream *file){rules.printRules(file);}
    void addCardToFoundations(int b,Card c);
    void printFoundations(){foundations.printFoundations();}
    void printFoundations(std::ofstream *file){foundations.printFoundations(file);}
    void addCardToTableau(int col, Card c){tableau.addCardToColumn(col,c);}
    void printTableau(){tableau.printTableau();}
    void addCardToStockWaste(Card c){stockWaste.addCardToSW(c);}
    void printStockWaste(){stockWaste.printStockWaste();}
    void addMove(Move c){moves.addMove(c);}
    bool gameInWinningConfiguration();
    int getCurrentNumberOfMoves();
    int getConfigurationHash();
    void setCurrentWasteResets(){wasteResets++;}
    int getCurrentWasteResets(){return wasteResets;}
    int CanDoSafeMoves();

    void printStockWast(std::ofstream *pOfstream);

    void printMoves(std::ofstream *pOfstream);
};


#endif //SOLITAIRE_GAMECONFIGURATION_H
