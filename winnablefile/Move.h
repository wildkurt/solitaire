//
// Created by wendellbest on 3/19/23.
//

#ifndef SOLITAIRE_MOVE_H
#define SOLITAIRE_MOVE_H


#include <fstream>

class Move {
private:
    char from;
    char to;
public:
    Move();
    Move(char f, char t);
    void printMove(std::ofstream *file);
};


#endif //SOLITAIRE_MOVE_H
