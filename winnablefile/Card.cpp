//
// Created by wendellbest on 6/6/22.
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
