//
// Created by wendellbest on 1/15/23.
//

#ifndef SOLITAIRE_RULES_H
#define SOLITAIRE_RULES_H

/**Rules object*/

class Rules{
private:
    bool turn3cards; //default is one
    bool resetsLimited; //limited or unlimited waste resets
    int resetLimit;
    int resetsRemaining;
public:
    Rules();
    ~Rules()=default;
    void setCardTurnover(bool c);
    void setResetsLimited(bool c);
    void setResetLimit(int c);
    void printRules();
};


#endif //SOLITAIRE_RULES_H
