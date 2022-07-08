//
// Created by wendellbest on 7/7/22.
//

#include "card.h"

card card::operator=(const card &old) {
    card temp;
    temp.suit = old.suit;
    temp.suit = old.suit;
    return temp;
}

bool card::rankIsValid(char rank) {
    bool result = false;
    if(rank == 'A' || rank == '2' || rank == '3' || rank == '4' || rank == '5' || rank == '6' || rank == '7'
    || rank == '8' || rank == '9' || rank == 'T' || rank == 'J' || rank == 'Q' || rank == 'K')
        result = true;
    return result;
}

bool card::suitIsvalid(char suit) {
    bool result = false;
    if(suit == 'c' || suit == 's' || suit == 'd' || suit == 'h')
        result = true;
    return result;
}

int card::rankValue(char rank) {
    switch(rank){
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
        default : return 0;
    }
}

char card::getRank() {
    return rank;
}

char card::getSuit() {
    return suit;
}

bool card::sameColorSuit(const card b) {
    bool result = false;
    if((this->suit == 'c' && b.suit == 'c' )||(this->suit == 'c' && b.suit == 's') || (this->suit == 's' && b.suit == 'c') ||
            (this->suit == 's' && b.suit == 's'))
        result = true;
    else if((this->suit == 'd' && b.suit == 'd' )||(this->suit == 'd' && b.suit == 'h') || (this->suit == 'h' && b.suit == 'h') ||
            (this->suit == 'h' && b.suit == 'd'))
        result = true;
    return result;
}



