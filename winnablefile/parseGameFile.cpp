//
// Created by wendellbest on 1/15/23.
//

#include <iostream>
#include <fstream>
#include <string>
#include "parseGameFile.h"

parseGameFile::parseGameFile() {
    inputfile=nullptr;
    game = gameConfiguration();
}

parseGameFile::parseGameFile(std::string inputfile, gameConfiguration game) {
    this->inputfile = inputfile;
    this->game = game;
}

gameConfiguration parseGameFile::getGameFromfile() {
    std::ifstream gameFile;
    std::string buffer;
    gameConfiguration tempGame;
    tempGame = gameConfiguration();

    if(!tempGame.rules.getRulesFromFile())
        std::cerr << "Unable to parse rules from file." << std::endl;


    return tempGame;
}
