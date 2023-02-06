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
    Moves()= default;
    Moves(const Moves &omoves);
    Moves &operator=(const Moves &omoves);
    ~Moves()=default;
    void addMove(Move move);
    void printMoves();
    std::string buildGameConfigNumber();
};


#endif //SOLITAIRE_MOVES_H
