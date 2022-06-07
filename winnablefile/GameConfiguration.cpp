//
// Created by wendellbest on 6/6/22.
//

#include "GameConfiguration.h"
GameConfiguration::GameConfiguration() = default;
GameConfiguration::GameConfiguration(Switches switches) {
    this->switches = switches;
}

Switches GameConfiguration::getSwitches() {
    return switches;
}

Rules GameConfiguration::getRules() {
    return rules;
}

Tableau GameConfiguration::getTableau() {
    return tableau;
}


