//
// Created by wendellbest on 11/23/23.
//

#ifndef SOLITAIRE_MOVES_H
#define SOLITAIRE_MOVES_H

typedef struct Move{
    char from;
    char to;
    char action;
}Move;

typedef  struct Moves{
    Move moves[200];
}Moves;

int isValidMove(char from, char to);
int isValidAction(char action);
void addMoveToMoves(Move move);
void printMoves(Moves *moves);

#endif //SOLITAIRE_MOVES_H
