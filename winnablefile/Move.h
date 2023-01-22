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
    char getFrom();
    char getTo();
    void setFrom(char c);
    void setTo(char c);
    static bool isMove(char from, char to);
    static bool isStockMove(char c);
};


#endif //SOLITAIRE_MOVE_H
