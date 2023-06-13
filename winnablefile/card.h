//
// Created by wendellbest on 3/19/23.
//

#ifndef SOLITAIRE_CARD_H
#define SOLITAIRE_CARD_H


class Card {
private:
    char rank;
    char suit;
    bool isCardCovered;
public:
    Card();
    Card(char r, char s, bool c);
    char getRank(){return rank;}
    char getSuit(){return suit;}
    bool checkIfCardIsCovered(){return isCardCovered;}
};


#endif //SOLITAIRE_CARD_H
