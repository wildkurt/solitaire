//
// Created by wendellbest on 3/18/23.
//

#ifndef SOLITAIRE_PARSEFILE_H
#define SOLITAIRE_PARSEFILE_H

#include <string>
#include "SearchSettings.h"
#include "gameConfiguration.h"

class ParseFile {
private:
    SearchSettings settings;
    GameConfiguration *game;
    GameConfiguration ngame;
    std::string suits = "shdc";
    std::string ranks = "A123456789TJQK_";
public:
    explicit ParseFile(GameConfiguration game);
    ParseFile(SearchSettings set, GameConfiguration *game);
    bool readGameFile();
    bool readGameFile(std::ifstream fileptr, GameConfiguration game);
};

#endif //SOLITAIRE_PARSEFILE_H
