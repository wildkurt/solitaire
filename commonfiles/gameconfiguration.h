//
// Created by wendellbest on 1/29/24.
//
#ifdef __cplusplus
extern "C"{
#endif

#ifndef SOLITAIRE_GAMECONFIGURATION_H
#define SOLITAIRE_GAMECONFIGURATION_H

#include "rules.h"
#include "foundations.h"
#include "tableau.h"
#include "stockwaste.h"

typedef struct GameConfiguration{
    Rules rules;
    Foundations foundation;
    Tableau tableau;
    StockWaste stockwaste;
} GameConfiguration;

void printTheGameConfiguration(GameConfiguration *game);
void getTheGameConfigFromFile(GameConfiguration *game, char *inputfile);
#endif //SOLITAIRE_GAMECONFIGURATION_H

#ifdef __cplusplus
}
#endif