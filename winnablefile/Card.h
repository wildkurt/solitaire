//
// Created by wende on 6/7/2022.
//

#ifndef SOLITAIRE_CARD_H
#define SOLITAIRE_CARD_H


class Card {
private:
    char rank;
    char suit;
    bool covered;
public:
    Card();
    Card(char rank, char suit, bool covered);
    Card(Card &card);
    ~Card()=default;
    Card &operator=(Card const &card);
    char getRank() const;
    char getSuit() const;
    static bool isValidRank(char c);
    static bool isValidSuit(char c);
    bool isCovered(){return covered;}
};


#endif //SOLITAIRE_CARD_H
