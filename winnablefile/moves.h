//
// Created by wendellbest on 3/19/23.
//

#ifndef SOLITAIRE_MOVES_H
#define SOLITAIRE_MOVES_H

#include <iostream>
#include <vector>
#include "Move.h"

class Moves {
private:
    std::vector <Move> moves;
public:
    void addMove(Move c);
    int numberOfMoves(){return moves.size();}
    int getHashOfMoves();

    void printMoves(std::ofstream *ofstream);
};


#endif //SOLITAIRE_MOVES_H
