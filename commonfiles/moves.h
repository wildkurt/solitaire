//
// Created by wendellbest on 11/23/23.
//

#ifndef SOLITAIRE_MOVES_H
#define SOLITAIRE_MOVES_H

#define MAX_BUFFER 200

typedef struct Move{
    char from;
    char to;
    char action;
}Move;

typedef  struct Moves{
    Move moves[200];
    int totalMoves;
}Moves;

int getMovesFromFile(char *buffer, char *readBuffer, FILE *inputFile, int *line, Moves *moves);
void addMoveToMoves(Move move, Moves *moves);
void printMoves(Moves *moves);
int validMoveFrom(char c);
int validMoveTo(char c);
int validAction(char c);

#endif //SOLITAIRE_MOVES_H
