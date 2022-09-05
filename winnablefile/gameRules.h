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
    gameRules();
    gameRules(const gameRules &old);
    gameRules& operator=(const gameRules &old);
    ~gameRules()= default;
    void getRules(std::__cxx11::basic_string<char> basicString);
    void printRules();
};


#endif //SOLITAIRE_GAMERULES_H
