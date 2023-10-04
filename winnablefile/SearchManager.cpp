//
// Created by wendellbest on 5/25/23.
//

#include "SearchManager.h"


bool SearchManager::run(SearchSettings *settings, GameConfiguration *game) {
    configurations++;
    game->setGameConfigurationVersion(configurations);

    //Is there a limit on the moves
    //Is a hash table cache required, if so, need to see if moves exist
    //Is safe moves to foundation enabled
    //Verbose mode
    //Is the game in a winning condition

    return false;
}
