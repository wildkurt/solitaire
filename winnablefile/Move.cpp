//
// Created by wendellbest on 1/15/23.
//

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
