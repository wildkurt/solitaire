//
// Created by wendellbest on 1/29/24.
//

#ifndef SOLITAIRE_RULES_H
#define SOLITAIRE_RULES_H

typedef struct Rules{
    //How mantimes can the waste be reset, -1 if unlimited
    int wasteResets;
    //How many card can be turned over from stockpile
    int cardTurnover;
}Rules;

#endif //SOLITAIRE_RULES_H
