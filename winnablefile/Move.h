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
public:
    Move();
    Move(char from, char to);
    Move(const Move &omove);
    Move &operator=(const Move &omove);
    ~Move()=default;
    char getFrom();
    char getTo();
};


#endif //SOLITAIRE_MOVE_H
