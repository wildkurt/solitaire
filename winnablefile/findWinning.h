//
// Created by wendellbest on 1/22/23.
//

#ifndef SOLITAIRE_FINDWINNING_H
#define SOLITAIRE_FINDWINNING_H


#include "SearchSettings.h"
#include "gameConfiguration.h"

class findWinning {
private:
public:
    findWinning();

    gameConfiguration winningGameSearch(SearchSettings settings, gameConfiguration configuration);
};


#endif //SOLITAIRE_FINDWINNING_H
