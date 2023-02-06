//
// Created by wendellbest on 1/15/23.
//

#ifndef SOLITAIRE_MOVE_H
#define SOLITAIRE_MOVE_H

/**Move object*/

class Move{
private:
    char from;
    char to;
    std::string foam;
    std::string toe;
public:
    Move();
    Move(char from, char to);
    Move(const Move &omove);
    Move &operator=(const Move &omove);
    ~Move()=default;
    char getFrom();
    char getTo();
    static bool isMove(char &i, char &i1);
    static bool isStockMove(char &i);
};


#endif //SOLITAIRE_MOVE_H
