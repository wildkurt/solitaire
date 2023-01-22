//
// Created by wendellbest on 1/15/23.
//

#include <iostream>
#include "Moves.h"

Moves::Moves() {

}

void Moves::addMove(Move move) {

}

Move Moves::getMoves() {
    return Move();
}

void Moves::printMoves() {
    for(std::vector<Move>::iterator itr = moves.begin(); itr != moves.end(); itr++){
        if(Move::isMove(itr->getFrom(),itr->getTo()))
            std::cout << itr->getFrom() << "->" << itr->getTo() << " ";
        else if(Move::isStockMove(itr->getFrom()))
            std::cout << itr->getFrom() << " ";
    }
}
