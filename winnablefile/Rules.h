//
// Created by wende on 6/7/2022.
//

#ifndef SOLITAIRE_RULES_H
#define SOLITAIRE_RULES_H

#include <fstream>

class Rules {
private:
    int turn;
    int limit;
public:
    Rules();
    ~Rules()=default;
    Rules(Rules const &rules);
    Rules &operator=(Rules const &rules);
    Rules findRules(const std::string& inputfilename);
    int getTurn();
    int getLimit();
};


#endif //SOLITAIRE_RULES_H
