//
// Created by wendellbest on 5/19/22.
//

#ifndef SOLITAIRE_RULES_H
#define SOLITAIRE_RULES_H


class Rules{
private:
    bool turn3;
    bool limited;
    int resetNumber;
public:
    Rules(){turn3 = false; limited = false, resetNumber = -1;}
    Rules(char turn, char limit, int number){turn3 = turn; limited = limit; resetNumber = number;}
    ~Rules()= default;
    void setTurn(bool c){turn3 = c;}
    void setLimit(bool c){limited = c;}
    void setResetNumber(int n){resetNumber = n;}
    bool getTurn(){return turn3;}
    bool getLimit(){return limited;}
    int getResetNumber(){return resetNumber;}
};


#endif //SOLITAIRE_RULES_H
