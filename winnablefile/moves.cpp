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

void Moves::printMoves(std::ofstream *ofstream) {
    std::vector<Move>::iterator itr = moves.begin();
    for(;itr != moves.end();itr++){
        if(itr->getFrom() == '|' || itr->getFrom() == '.' || itr->getFrom() == 'r')
            *ofstream << itr->getFrom() << std::endl;
        else
            *ofstream << itr->getFrom() << "->" << itr->getTo() <<std::endl;
    }
}


