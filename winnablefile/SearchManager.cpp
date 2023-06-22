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
    for(int i = 0; i < cardFrom.size(); i++){
        for(int j = 0; j < cardTo.size(); j++){
            //Don't check if from and to are sae place
            if(cardFrom[i] == cardTo[j]){
                continue;
            }
            else{
                /* 1. Create a move
                 * 2. If cache mode is selected, create hash of moves including new one
                 *      a. Check hash table
                 *      b. If it exists, continue
                 *      c. If it doesn't exist, test new move
                * 3. Things to update:
                 *  a. Number of moves, and determine if more moves remain
                 *  b. Number of configurations
                 *  c. remaining waste resets*/
            }
        }
    }
    return false;
}
