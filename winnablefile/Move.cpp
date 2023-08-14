//
// Created by wendellbest on 3/19/23.
//

#include "Move.h"

Move::Move() {from = '0'; to = '0';}

Move::Move(char f, char t) {from = f; to = t;}

int Move::getMoveValue(char c) {
    int result = 0;
    switch(c){
        case '1' : result = 1; break;
        case '2' : result = 2; break;
        case '3' : result = 3; break;
        case '4' : result = 4; break;
        case '5' : result = 5; break;
        case '6' : result = 6; break;
        case '7' : result = 7; break;
        case 'w' : result = 8; break;
        case 'f' : result = 9; break;
        case '.' : result = 10; break;
        case 'r' : result = 11; break;
        default : result = 0;
    }
    return result;
}

Move& Move::operator=(Move const &move) {
    this->from = move.from;
    this->to = move.to;
    return *this;
}


