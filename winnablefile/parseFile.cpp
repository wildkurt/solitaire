//
// Created by wendellbest on 3/18/23.
//
#include <iostream>
#include <fstream>
#include "parseFile.h"
#include "gameConfiguration.h"


ParseFile::ParseFile(SearchSettings set, GameConfiguration game) {
    settings = set;
    this->game = game;
}

bool ParseFile::readGameFile() {
    std::ifstream inputFile(settings.getFilename());
    std::string buffer;
    while(getline(inputFile,buffer)){
        std::cout << buffer << std::endl;
    }
    inputFile.close();
    return false;
}
