//
// Created by wende on 6/7/2022.
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
    static bool isValidRank(char c);
    static bool isValidSuit(char c);
};


#endif //SOLITAIRE_CARD_H
