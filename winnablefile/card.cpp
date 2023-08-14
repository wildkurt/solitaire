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

Card& Card::operator=(const Card *otr) {
    this->rank = otr->rank;
    this->suit = otr->suit;
    this->isCardCovered = otr->isCardCovered;
    return *this;
}

char Card::cardColorIs() {
    char result;
    if(suit == 'c' || suit == 's')
        result = 'b';
    else if(suit == 'd' || suit == 'h')
        result = 'r';
    return result;
}

int Card::cardRankValueIs() {
    int result = 0;
    switch(rank){
        case 'A' : result = 1; break;
        case '2' : result = 2; break;
        case '3' : result = 3; break;
        case '4' : result = 4; break;
        case '5' : result = 5; break;
        case '6' : result = 6; break;
        case '7' : result = 7; break;
        case '8' : result = 8; break;
        case '9' : result = 9; break;
        case 'T' : result = 10; break;
        case 'J' : result = 11; break;
        case 'Q' : result = 12; break;
        case 'K' : result = 13; break;
        default : return result;
    }
    return result;
}


