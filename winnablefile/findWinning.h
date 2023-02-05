//
// Created by wendellbest on 1/22/23.
//

#ifndef SOLITAIRE_FINDWINNING_H
#define SOLITAIRE_FINDWINNING_H


#include "SearchSettings.h"
#include "gameConfiguration.h"
class findWinning {
private:
    SearchSettings settings;
    gameConfiguration initialGame;
    char from[9]="w1234567";
    char to[9]="1234567f";
    long int configCount = 0;
public:
    explicit findWinning(SearchSettings settings, gameConfiguration game);
    findWinning& operator=(findWinning const& findb);
    bool winningGameSearch();
    void incrementConfigCount(){configCount++;}
    bool writeToAdvance(char rom, char tO, gameConfiguration configuration);
};


#endif //SOLITAIRE_FINDWINNING_H
