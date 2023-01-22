//
// Created by wendellbest on 1/15/23.
//

#include <string>
#include "Card.h"

Card::Card() {
    rank = 0;
    suit = 0;
    covered = true;
}

Card::Card(char rank, char suit, bool covered) {
    this->rank = rank;
    this->suit = suit;
    this->covered = covered;
}

char Card::getRank() {
    return rank;
}

char Card::getCardSuit() {
    return suit;
}

void Card::setRank(char c) {
    rank = c;
}

void Card::setSuit(char c) {
    suit = c;
}

int Card::getRankValue(char c) {
    switch (c){
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

bool Card::isCovered() {
    return covered;
}

void Card::setCovered(bool c) {
    covered = c;
}

bool Card::isCardRank(char c) {
    std::string ranks = "A23456789TJQK";
    if(ranks.find(c) != std::string::npos)
        return true;
    else
        return false;
}

bool Card::isCardSuit(char c) {
    std::string suit = "chds";
    if(suit.find(c)!=std::string::npos)
        return true;
    else
        return false;
}
