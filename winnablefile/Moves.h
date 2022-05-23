//
// Created by wendellbest on 5/20/22.
//

#ifndef SOLITAIRE_MOVES_H
#define SOLITAIRE_MOVES_H


#include "cardHeader.h"

class Moves {
private:
    char from;
    char to;
    char action;
public:
    Moves(){
        from = '_';
        to = '_';
        action = '_';
    }
    Moves(char f, char t){ from = f; to = t;}
    Moves(char a){action = a;}
    ~Moves();
    void setFrom(char f){from = f;}
    void setTo(char t){to = t;}
    void setAction(char a){action = a;}
    char getFrom(){return from;}
    char getTo(){return to;}
    char getAction(){return action;}
};


#endif //SOLITAIRE_MOVES_H
