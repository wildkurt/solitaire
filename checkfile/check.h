//
// Created by wendellbest on 3/8/22.
//

#ifndef SOLITAIRE_CHECK_H
#define SOLITAIRE_CHECK_H
typedef struct {
    char rank;
    char suit;
    char covered;
    char stock;
    char waste;
}Card;

int isRank(char c);
int isSuit(char c);
int rankValue(char c);
char valueRank(int c);
int findFoundations(char *buffer, FILE *input, int *line, Card *foundations);
int findTableaus(FILE *input, int *line, Card *t7, Card *t6, Card *t5, Card *t4, Card *t3,Card *t2, Card *t1);
int findStockWaste(char *buffer, FILE *input, int *line, Card *sw);
void countCards(Card *foundations, int *club, int *diamond, int *heart, int *spade, Card *t7, Card *t6, Card *t5, Card *t4, Card *t3,Card *t2, Card *t1, Card *sw);
void printCards(Card *arr, int size);
char isRedOrBlack(char c);
int checkTableaus(Card *t7, Card *t6, Card *t5, Card *t4, Card *t3,Card *t2, Card *t1);
#endif //SOLITAIRE_CHECK_H
