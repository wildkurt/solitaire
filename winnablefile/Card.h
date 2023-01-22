//
// Created by wendellbest on 1/15/23.
//

#ifndef SOLITAIRE_CARD_H
#define SOLITAIRE_CARD_H

/**The Card Object*/
class Card{
private:
    char rank;
    char suit;
    bool covered;
public:
    Card();
    Card(char rank, char suit, bool covered);
    char getRank();
    char getCardSuit();
    void setRank(char c);
    void setSuit(char c);
    int getRankValue(char c);
    bool isCovered();
    void setCovered(bool c);
    static bool isCardRank(char c);
    static bool isCardSuit(char c);
};


#endif //SOLITAIRE_CARD_H
