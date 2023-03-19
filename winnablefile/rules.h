//
// Created by wendellbest on 3/18/23.
//

#ifndef SOLITAIRE_RULES_H
#define SOLITAIRE_RULES_H


class Rules {
private:
    //true means turn three cards over
    bool turn3cards;
    //true, waste resets are limited
    bool limitedWasteReset;
    //number of allowed resets
    int numberOfWasteResets;
public:
    Rules();
    void setCardTurnover(bool c){turn3cards = c;}
    bool getCardTurnover(){return turn3cards;}
    void setLimitedWasteResets(bool c){limitedWasteReset = c;}
    bool getLimitedWasteResets(){return limitedWasteReset;}
    void setNumberOfWasteResets(int c){numberOfWasteResets = c;}
    int getNumberOfWasteResets(){return numberOfWasteResets;}
};


#endif //SOLITAIRE_RULES_H
