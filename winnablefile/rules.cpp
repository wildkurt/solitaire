//
// Created by wendellbest on 1/15/23.
//

#include <iostream>
#include <fstream>
#include <string>
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

Rules::Rules(const Rules &rules) {
    turn3cards = rules.turn3cards;
    resetsLimited = rules.resetsLimited;
    resetLimit = rules.resetLimit;
    resetsRemaining = rules.resetsRemaining;
}

Rules &Rules::operator=(const Rules &rules) {
    turn3cards = rules.turn3cards;
    resetsLimited = rules.resetsLimited;
    resetLimit = rules.resetLimit;
    resetsRemaining = rules.resetsRemaining;
    return *this;
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

void Rules::setRuleTurn(bool c) {
    turn3cards = c;
}

void Rules::setRuleLimitNumber(int i) {
    resetLimit = i;
}

void Rules::setRuleLimits(bool c) {
    resetsLimited = c;
}




