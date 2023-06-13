//
// Created by wendellbest on 5/25/23.
//

#include "SearchManager.h"
SearchManager::SearchManager(GameConfiguration *gam, SearchSettings set) {
    game = gam;
    settings = set;
}

bool SearchManager::run() {
    GameConfiguration recursiveGame;
    recursiveGame = *game;
    if(recursiveSearch(recursiveGame))
        return true;
    else
        return false;
}

bool SearchManager::recursiveSearch(GameConfiguration recGame) {
    //check for winning condition
    if(recGame.gameInWinningConfiguration()){
        *game = recGame;
        return true;
    }
    //Check for safe moves for every tested move
    return false;
}
