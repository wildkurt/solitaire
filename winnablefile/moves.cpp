//
// Created by wendellbest on 3/19/23.
//

#include "moves.h"

void Moves::addMove(Move c) {
    moves.push_back(c);
}

int Moves::getHashOfMoves() {
    int result = 0;
    int multiplier = 1;
    auto iter = moves.begin();

    for(; iter < moves.end(); iter++){
        char from = iter->getFrom();
        char to = iter->getTo();
        if(from == '.' || from == 'r')
            result = result + multiplier++ * iter->getMoveValue(from);
        else{
            result = result + multiplier++ * iter->getMoveValue(from);
            result = result + multiplier++ * iter->getMoveValue(to);
        }

    }
    return result;
}


