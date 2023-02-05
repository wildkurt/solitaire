//
// Created by wendellbest on 1/15/23.
//

#ifndef SOLITAIRE_PARSEGAMEFILE_H
#define SOLITAIRE_PARSEGAMEFILE_H
#include <string>
#include "gameConfiguration.h"

/** 1. Open game file and retrieve the content
 * 2. Rules with turn and limit
 * 3. Foundation
 * 4. Tableau
 * 5. Stock*/
class parseGameFile {
private:
    std::string inputfile;
    gameConfiguration game;
public:
    parseGameFile();
    parseGameFile(std::string inputfile, gameConfiguration game);
    parseGameFile(const parseGameFile& parser);
    parseGameFile & operator=(const parseGameFile& parser);
    ~parseGameFile()=default;
    gameConfiguration getGameFromfile();
};


#endif //SOLITAIRE_PARSEGAMEFILE_H
