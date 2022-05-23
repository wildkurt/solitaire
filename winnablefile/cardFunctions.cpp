//
// Created by wendellbest on 5/19/22.
//
#include "cardHeader.h"

int Card::rankValue(char c){
    switch(c){
        case 'A' : return 1;
        case '2' : return 2;
        case '3' : return 3;
        case '4' : return 4;
        case '5' : return 5;
        case '6' : return 6;
        case '7' : return 7;
        case '8' : return 8;
        case '9' : return 9;
        case 'T' : return 10;
        case 'J' : return 11;
        case 'Q' : return 12;
        case 'K' : return 13;
        default: return 0;
    }
}

Card::Card(Card &p){
    this->rank = p.rank;
    this->suit = p.suit;
    this->covered = p.covered;
}

Card::Card(const Card &p) {
    this->rank = p.rank;
    this->suit = p.suit;
    this->covered = p.covered;
}

Card& Card::operator=(Card *p) {
    this->rank = p->rank;
    this->suit = p->suit;
    this->covered = p->covered;
    return *this;
}


