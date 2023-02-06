//
// Created by wendellbest on 1/15/23.
//

#include <iostream>
#include "Moves.h"

Moves::Moves(const Moves &omoves) {
    this->moves = omoves.moves;
}

Moves &Moves::operator=(const Moves &omoves) {
    this->moves = omoves.moves;
    return *this;
}

void Moves::addMove(Move move) {
    moves.push_back(move);
}

void Moves::printMoves() {
    std::cout<< std::endl;
    std::cout << "Moves: ";
    for(std::vector<Move>::iterator itr = moves.begin(); itr != moves.end(); itr++){
        if(itr->getFrom() != '.' || itr->getFrom() != 'r')
            std::cout << itr->getFrom() << std::endl;
        else
            std::cout << itr->getFrom() << "->" << itr->getTo() << std::endl;
    }
    std::cout << std::endl;
}
// Characters are "1, 2, 3, 4, 5, 6, 7, . , r, w, f"
std::string Moves::buildGameConfigNumber() {
    std::string strNumber = "";
    if(moves.empty())
        return 0;
    for(std::vector<Move>::iterator itr = moves.begin(); itr != moves.end(); itr++){
        strNumber.push_back(itr->getFrom());
        strNumber.push_back(itr->getTo());
    }
    return strNumber;
}



