//
// Created by wende on 6/7/2022.
//

#ifndef SOLITAIRE_GAMECONFIGURATION_H
#define SOLITAIRE_GAMECONFIGURATION_H

#include <string>
#include "Rules.h"
#include "Foundation.h"
#include "Tableau.h"
#include "Stock.h"

class GameConfiguration {
private:
    std::string inputfilename;
    Rules rules;
    Foundation foundation;
    Tableau tableau;
    Stock stock;
public:
    GameConfiguration()=default;
    explicit GameConfiguration(std::string inputfilename);
    int getRulesTurn();
    int getRulesLimit();
    bool isGameFoundationFilled();
    void printGameFoundation();
    void printGameTableau();
    void printGameStock();
};


#endif //SOLITAIRE_GAMECONFIGURATION_H
