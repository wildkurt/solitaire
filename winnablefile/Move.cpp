//
// Created by wendellbest on 3/19/23.
//

#include "Move.h"

Move::Move() {from = '0'; to = '0';}

Move::Move(char f, char t) {from = f; to = t;}

void Move::printMove(std::ofstream *file) {
    if(from == '.')
        *file << '.';
    else if(from == 'r')
        *file << 'r';
    else
        *file << from << "->" << to;
}
