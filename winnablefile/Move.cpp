//
// Created by wendellbest on 1/15/23.
//

#include <string>
#include "Move.h"

Move::Move() {
    from = 0;
    to = 0;
    foam = "w1234567";
    toe = "1234567f";
}

Move::Move(char from, char to) {
    this->from = from;
    this->to = to;
    foam = "w1234567";
    toe = "1234567f";
}

Move::Move(const Move &omove) {
    from = omove.from;
    to = omove.to;
}

Move &Move::operator=(const Move &omove) {
    from = omove.from;
    to = omove.to;
    return *this;
}

char Move::getFrom() {
    return from;
}

char Move::getTo() {
    return to;
}

bool Move::isMove(char &i, char &i1) {
    if(foam.find(i)!=std::string::npos && toe.find(i1)!=std::string::npos)
        return true;
    return false;
}

bool Move::isStockMove(char &i) {
    if(i == '.' || i == 'r')
        return true;
    return false;
}




