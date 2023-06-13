//
// Created by wendellbest on 5/25/23.
//

#ifndef SOLITAIRE_SEARCHMANAGER_H
#define SOLITAIRE_SEARCHMANAGER_H
#include <map>
#include "gameConfiguration.h"
#include "SearchSettings.h"

class SearchManager {
private:
    GameConfiguration *game;
    SearchSettings settings;
    int configurations = 0;
    std::map <int, GameConfiguration> hashtable;
    std::string cardFrom = "w1234567.r";
    std::string cardTo = "1234567f";
public:
    SearchManager(GameConfiguration *gam, SearchSettings set);
    bool run();
    bool recursiveSearch(GameConfiguration game);
};



#endif //SOLITAIRE_SEARCHMANAGER_H
