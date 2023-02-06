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
    findWinning(SearchSettings settings, gameConfiguration &game);
    findWinning(const findWinning &wgame);
    findWinning& operator=(findWinning const& findb);
    ~findWinning()=default;
    bool winningGameSearch(gameConfiguration game);
    void incrementConfigCount(){configCount++;}
    bool writeToAdvance(char rom, char tO, gameConfiguration configuration);
};


#endif //SOLITAIRE_FINDWINNING_H
