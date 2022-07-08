//
// Created by wendellbest on 6/12/22.
//

#include "Moves.h"
#include <iostream>

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
/*Returns false if the source is 'f' or destination is 'w'.
 * Also returns false for '.' and 'r' since they are not card
 * movements, just a move*/
bool Moves::isMoveValid() {
    bool result = true;
    if(this->src == 'f' || this->dst == 'w' || this->src == '.' || this->src == 'r' || this->dst == '.' || this->dst == 'r')
        result = false;
    return result;
}

void Moves::printMove() {
    if(this->src == '.' || this->src == 'r')
        std::cout << this->src << std::endl;
    else
        std::cout << this->src << "->" << this->dst << std::endl;
}
