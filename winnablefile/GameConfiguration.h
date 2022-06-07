//
// Created by wendellbest on 6/6/22.
//

#ifndef SOLITAIRE_GAMECONFIGURATION_H
#define SOLITAIRE_GAMECONFIGURATION_H


#include "Rules.h"
#include "Foundation.h"
#include "Tableau.h"
#include "Stock.h"
#include "Switches.h"

class GameConfiguration {
private:
    Rules rules;
    Foundation foundation;
    Tableau tableau;
    Stock stock;
    Switches switches;
public:
    GameConfiguration();
    explicit GameConfiguration(Switches switches);
    Switches getSwitches();
    Rules getRules();
    Tableau getTableau();
};


#endif //SOLITAIRE_GAMECONFIGURATION_H
