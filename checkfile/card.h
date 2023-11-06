//
// Created by wende on 5/30/2022.
//

#ifndef SOLITAIRE_CARD_H
#define SOLITAIRE_CARD_H
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
