//
// Created by wende on 6/7/2022.
//

#include "Card.h"

Card::Card() {
    rank = 0;
    suit = 0;
}

Card::Card(char rank, char suit) {
    this->rank = rank;
    this->suit = suit;
}

char Card::getRank() {
    return rank;
}

char Card::getSuit() {
    return suit;
}

bool Card::isValidRank(char c) {
    bool result = false;
    if(c == 'A' || c == 'J' || c=='Q' || c=='K')
        result = true;
    else if(c >= '2' && c <= '9')
        result = true;
    return result;
}

bool Card::isValidSuit(char c) {
    bool result = false;
    if(c == 'c' || c == 'd' || c == 'h' || c == 's')
        result = true;
    return result;
}
