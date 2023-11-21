//
// Created by wendellbest on 11/5/23.
//

#ifndef SOLITAIRE_GAMECONFIGURATION_H
#define SOLITAIRE_GAMECONFIGURATION_H

#define MAX_BUFFER 200

#include "rules.h"
#include "foundation.h"
#include "tableau.h"
#include "stockWaste.h"

typedef struct GameConfiguration{
    Rules rules;
    Foundation foundation;
    Tableau tableau;
    StockWaste stockwaste;
    int found;
}GameConfiguration;

#endif //SOLITAIRE_GAMECONFIGURATION_H
