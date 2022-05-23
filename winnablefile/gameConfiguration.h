//
// Created by wendellbest on 5/19/22.
//

#ifndef SOLITAIRE_GAMECONFIGURATION_H
#define SOLITAIRE_GAMECONFIGURATION_H

#include "rules.h"
#include "cardHeader.h"
#include "switches.h"
#include "foundations.h"
#include "Tableaus.h"
#include "StockWaste.h"
#include "Moves.h"
#include <list>

class GameConfiguration{
private:
    Rules rules;
    Switches switches;
    foundations foundation;
    Tableaus tableau;
    StockWaste stockwaste;
    std::list<Moves> moves;
public:
    explicit GameConfiguration(Switches p);
    ~GameConfiguration()=default;
    int parseInputFile(Switches input);
    bool isValidRank(char c);
    void printCardArrays();
    bool isValidSuit(char c);
    bool isValidFromMove(char c);
    bool isValidToMove(char c);
    bool isValidAction(char c);
};


#endif //SOLITAIRE_GAMECONFIGURATION_H
