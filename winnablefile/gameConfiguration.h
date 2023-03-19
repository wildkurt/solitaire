//
// Created by wendellbest on 3/18/23.
//

#ifndef SOLITAIRE_GAMECONFIGURATION_H
#define SOLITAIRE_GAMECONFIGURATION_H


#include "rules.h"

class GameConfiguration {
private:
    Rules rules;
public:
    GameConfiguration()= default;
    bool getRuleCardTurnover(){return rules.getCardTurnover();}
    bool getRuleLimitedWasteResets(){return rules.getLimitedWasteResets();}
    int getRuleNumberofWasteResets(){return rules.getNumberOfWasteResets();}
    void setRuleCardTurnover(bool c){return rules.setCardTurnover(c);}
    void setRuleLimitedWasteResets(bool c){rules.setLimitedWasteResets(c);}
    void setRuleNumberofWasteResets(int c){rules.setNumberOfWasteResets(c);}
};


#endif //SOLITAIRE_GAMECONFIGURATION_H
