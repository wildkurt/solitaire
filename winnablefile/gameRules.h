//
// Created by wendellbest on 7/7/22.
//

#ifndef SOLITAIRE_GAMERULES_H
#define SOLITAIRE_GAMERULES_H


#include <string>

class gameRules {
private:
    std::string filename;
    int numCardsToTurnOver;
    int numOfWasteResets;
public:
    void getRules(std::__cxx11::basic_string<char> basicString);
};


#endif //SOLITAIRE_GAMERULES_H
