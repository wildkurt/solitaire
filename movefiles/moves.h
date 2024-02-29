//
// Created by wendellbest on 2/5/24.
//

#ifndef SOLITAIRE_MOVES_H
#define SOLITAIRE_MOVES_H

#define MAX_BUFFER 400

typedef struct Move{
    char to;
    char from;
    char actionn;
}Move;

typedef struct Moves{
    Move moves[MAX_BUFFER];
}Moves;

int getMoves(Move *moves, FILE *inputfile, char *buffer);
void printMoves(Moves *moves);

#endif //SOLITAIRE_MOVES_H
