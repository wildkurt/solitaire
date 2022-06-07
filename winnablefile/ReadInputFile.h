//
// Created by wendellbest on 6/6/22.
//

#ifndef SOLITAIRE_READINPUTFILE_H
#define SOLITAIRE_READINPUTFILE_H

#include "GameConfiguration.h"
#include "Switches.h"

class ReadInputFile {
private:
    GameConfiguration gameconfiguration;
public:
    explicit ReadInputFile(GameConfiguration gameConfiguration);
    void getFileInput();
};


#endif //SOLITAIRE_READINPUTFILE_H
