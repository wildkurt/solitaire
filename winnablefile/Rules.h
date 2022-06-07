//
// Created by wendellbest on 6/6/22.
//

#ifndef SOLITAIRE_RULES_H
#define SOLITAIRE_RULES_H

#include <string>

class Rules {
private:
    int turnover;
    int limit;
public:
    Rules();
    void setTurnOver(std::string turnover);
    void setLimit(std::string limit);
    int findRules(std::string filename);
};


#endif //SOLITAIRE_RULES_H
