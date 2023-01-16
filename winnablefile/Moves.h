//
// Created by wendellbest on 1/15/23.
//

#ifndef SOLITAIRE_MOVES_H
#define SOLITAIRE_MOVES_H

/**Moves Object*/

#include <vector>
#include "Move.h"

class Moves{
private:
    std::vector <Move> moves;
public:
    Moves();
    void addMove(Move move);
    Move getMoves();
};


#endif //SOLITAIRE_MOVES_H
