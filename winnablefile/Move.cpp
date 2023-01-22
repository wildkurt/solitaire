//
// Created by wendellbest on 1/15/23.
//

#include <string>
#include "Move.h"

Move::Move() {
    from = 0;
    to = 0;
}

Move::Move(char from, char to) {
    this->from = from;
    this->to = to;
}

char Move::getFrom() {
    return from;
}

char Move::getTo() {
    return to;
}

void Move::setFrom(char c) {
    from = c;
}

void Move::setTo(char c) {
    to = c;
}

bool Move::isMove(char from, char to) {
    std::string fromStr = "w1234567";
    std::string toStr = "1234567f";

    if(fromStr.find(from)!= std::string::npos && toStr.find(to)!= std::string::npos)
        return true;
    else
    return false;
}

bool Move::isStockMove(char c) {
    std::string altStr = ".r";
    if(altStr.find(c) != std::string::npos)
        return true;
    else
        return false;
}
