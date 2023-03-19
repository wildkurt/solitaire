//
// Created by wendellbest on 3/18/23.
//

#ifndef SOLITAIRE_PARSEFILE_H
#define SOLITAIRE_PARSEFILE_H


#include "SearchSettings.h"
#include "gameConfiguration.h"

class ParseFile {
private:
    SearchSettings settings;
    GameConfiguration game;
public:
    ParseFile(SearchSettings set, GameConfiguration game);
    bool readGameFile();
};

#endif //SOLITAIRE_PARSEFILE_H
