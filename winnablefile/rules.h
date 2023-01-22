//
// Created by wendellbest on 1/15/23.
//

#ifndef SOLITAIRE_RULES_H
#define SOLITAIRE_RULES_H

#include <string>
#include "gameConfiguration.h"

/**Rules object*/

class Rules{
private:
    bool turn3cards; //default is one
    bool resetsLimited; //default is unlimited
    int resetLimit;
    int resetsRemaining;
public:
    Rules();
    Rules(bool cardTurn, bool limit, int numLimit);
    bool getTurn3Cards();
    bool getResetsLimited();
    int getResetLimit();
    int getRemainingResets();
    void incrementReset();
    void setRuleTurn(bool c);
    void setRuleLimits(bool c);
    void setRuleLimitNumber(int i);
};


#endif //SOLITAIRE_RULES_H
