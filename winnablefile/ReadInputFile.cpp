//
// Created by wendellbest on 6/6/22.
//

#include "ReadInputFile.h"
#include <iostream>
#include <fstream>


ReadInputFile::ReadInputFile(GameConfiguration gameConfiguration) {
    this->gameconfiguration = gameConfiguration;
}

void ReadInputFile::getFileInput() {
    if(gameconfiguration.getRules().findRules(gameconfiguration.getSwitches().getInputFileName())){
        std::cerr << "Unable to get rules for game" << std::endl;
    }
}