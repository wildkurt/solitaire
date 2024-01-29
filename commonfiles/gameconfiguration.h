//
// Created by wendellbest on 1/29/24.
//

#ifndef SOLITAIRE_GAMECONFIGURATION_H
#define SOLITAIRE_GAMECONFIGURATION_H

#include "rules.h"
#include "foundations.h"
#include "tableau.h"
#include "stockwaste.h"

#define MAX_BUFFER 200

typedef struct GameConfiguration{
    Rules rules;
    Foundations foundation;
    Tableau tableau;
    StockWaste stockwaste;
} GameConfiguration;

#endif //SOLITAIRE_GAMECONFIGURATION_H
