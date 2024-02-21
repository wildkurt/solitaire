//
// Created by wendellbest on 1/29/24.
//

#ifndef SOLITAIRE_CARD_H
#define SOLITAIRE_CARD_H

typedef struct Card{
    char rank;
    char suit;
    char faceUp;
    int cardCount;
}Card;

int isRank(char c);
int isSuit(char c);
char getRank(int c);
int isSameColor(char c, char d);
#endif //SOLITAIRE_CARD_H
