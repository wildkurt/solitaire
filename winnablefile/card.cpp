//
// Created by wendellbest on 3/19/23.
//

#include "card.h"

Card::Card() {
    rank = '0';
    suit = '0';
    isCardCovered = false;
}

Card::Card(char r, char s, bool c) {
    rank = r;
    suit = s;
    isCardCovered = c;
}
