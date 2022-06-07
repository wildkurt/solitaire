//
// Created by wendellbest on 6/6/22.
//

#ifndef SOLITAIRE_CARD_H
#define SOLITAIRE_CARD_H


class Card {
private:
    char rank;
    char suit;
public:
    Card();
    Card(char rank, char suit);
    char getRank();
    char getSuit();
};


#endif //SOLITAIRE_CARD_H
