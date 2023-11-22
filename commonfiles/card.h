//
// Created by wendellbest on 11/22/23.
//

#ifndef SOLITAIRE_CARD_H
#define SOLITAIRE_CARD_H

#define MAX_BUFFER 200

typedef struct Card{
    char rank;
    char suit;
    char covered;
    char stock;
}Card;

int isRank(char c);
int isSuit(char c);
char isRedOrBlack(char c);
int rankValue(char c);
char valueRank(int c);

#endif //SOLITAIRE_CARD_H
