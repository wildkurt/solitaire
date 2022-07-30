//
// Created by wendellbest on 7/7/22.
//

#ifndef SOLITAIRE_CARD_H
#define SOLITAIRE_CARD_H


class card {
private:
    char rank;
    char suit;
public:
    card(){
        rank = 0;
        suit = 0;
    }
    card(char rank, char suit){
        this->rank = rank;
        this->suit = suit;
    }
    card(const card &old){
        this->rank = old.rank;
        this->suit = old.suit;
    }
    card operator=(const card &old);
    static bool rankIsValid(char rank);
    static bool suitIsvalid(char suit);
    int rankValue(char rank);
    char getRank();
    char getSuit();
    bool sameColorSuit(const card b);
    void setRank(char c){rank = c;}
    void setSuit(char c){suit = c;}
};


#endif //SOLITAIRE_CARD_H
