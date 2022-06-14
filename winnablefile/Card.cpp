//
// Created by wende on 6/7/2022.
//

#include "Card.h"

Card::Card() {
    rank = 0;
    suit = 0;
    covered = false;
}

Card::Card(char rank, char suit, bool covered) {
    this->rank = rank;
    this->suit = suit;
    this->covered = covered;
}

Card::Card(Card &card) {
    this->rank = card.rank;
    this->suit = card.suit;
    this->covered = card.covered;
}

Card &Card::operator=(Card const &card) {
    this->rank = card.rank;
    this->suit = card.suit;
    this->covered = card.covered;
    return *this;
}

char Card::getRank() const {
    return rank;
}

char Card::getSuit() const {
    return suit;
}

bool Card::isValidRank(char c) {
    bool result = false;
    if(c == 'A' || c == 'J' || c=='Q' || c=='K' || (c >= '2' && c <= '9'))
        result = true;
    return result;
}

bool Card::isValidSuit(char c) {
    bool result = false;
    if(c == 'c' || c == 'd' || c == 'h' || c == 's')
        result = true;
    return result;
}


