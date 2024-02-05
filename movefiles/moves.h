//
// Created by wendellbest on 2/5/24.
//

#ifndef SOLITAIRE_MOVES_H
#define SOLITAIRE_MOVES_H

#define MAX_BUFFER 200

typedef struct Move{
    char to;
    char from;
    char actionn;
}Move;

typedef struct Moves{
    Move moves[MAX_BUFFER];
}Moves;

void printMoves(Moves *moves);

#endif //SOLITAIRE_MOVES_H
