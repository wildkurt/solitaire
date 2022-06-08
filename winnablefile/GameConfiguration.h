//
// Created by wende on 6/7/2022.
//

#ifndef SOLITAIRE_GAMECONFIGURATION_H
#define SOLITAIRE_GAMECONFIGURATION_H

#include <string>
#include "Rules.h"
#include "Foundation.h"

class GameConfiguration {
private:
    std::string inputfilename;
    Rules rules;
    Foundation foundation;
public:
    GameConfiguration()=default;
    explicit GameConfiguration(std::string inputfilename);
    int getRulesTurn();
    int getRulesLimit();
    bool isGameFoundationFilled();
};


#endif //SOLITAIRE_GAMECONFIGURATION_H
