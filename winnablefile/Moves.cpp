//
// Created by wendellbest on 6/12/22.
//

#include "Moves.h"
Moves::Moves(char src, char dst){
    this->src = src;
    this->dst = dst;
}

Moves::Moves(const Moves &moves) {
    this->src = moves.src;
    this->dst = moves.dst;
}

Moves &Moves::operator=(const Moves &moves) {
    this->src = moves.src;
    this->dst = moves.dst;
    return *this;
}

bool Moves::isMoveValid() {
    bool result = true;
    if(this->src == 'f' || this->dst == 'w' || this->src == '.' || this->src == 'r')
        result = false;
    return result;
}
