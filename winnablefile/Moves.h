//
// Created by wendellbest on 6/12/22.
//

#ifndef SOLITAIRE_MOVES_H
#define SOLITAIRE_MOVES_H


class Moves {
private:
    char src;
    char dst;
public:
    Moves()=default;
    ~Moves()=default;
    Moves(char src, char dst);
    Moves(Moves const &moves);
    Moves &operator=(Moves const &moves);
    bool isMoveValid();
    char getSrc(){return src;}
    char getDst(){return dst;}
    void printMove();
};


#endif //SOLITAIRE_MOVES_H
