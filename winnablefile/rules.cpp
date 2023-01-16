//
// Created by wendellbest on 1/15/23.
//

#include "rules.h"

Rules::Rules() {
    turn3cards = false;
    resetsLimited = false;
    resetLimit = -1;
    resetsRemaining = -1;
}

Rules::Rules(bool cardTurn, bool limit, int numLimit) {
    turn3cards = cardTurn;
    resetsLimited = limit;
    resetLimit = numLimit;
    resetsRemaining = 0;
}

bool Rules::getTurn3Cards() {
    return turn3cards;
}

bool Rules::getResetsLimited() {
    return resetsLimited;
}

int Rules::getResetLimit() {
    return resetLimit;
}

int Rules::getRemainingResets() {
    return resetLimit - resetsRemaining;
}

void Rules::incrementReset() {
    resetsRemaining++;
}
