//
// Created by wendellbest on 3/18/23.
//

#include <iostream>
#include <fstream>
#include <string>
#include "rules.h"

Rules::Rules() {
    turn3cards = false;
    resetsLimited = false;
    resetLimit = -1;
    resetsRemaining = 0;
}

void Rules::setCardTurnover(bool c) {
    turn3cards = c;
}

void Rules::setResetsLimited(bool c) {
    resetsLimited = c;
}

void Rules::setResetLimit(int c) {
    resetLimit = c;
}

void Rules::printRules() {
    std::cout<< "Turn over 3 cards is: " << turn3cards << std::endl;
    std::cout<< "Is there a limit on waste resets: " << resetsLimited << std::endl;
    std::cout<< "Number of waste resets allowed: " << resetLimit << std::endl;
    std::cout<< "Number of resets left: " << resetsRemaining << std::endl;
}
