//
// Created by wendellbest on 7/7/22.
//

#ifndef SOLITAIRE_CARD_H
#define SOLITAIRE_CARD_H


class card {
private:
    char rank;
    char suit;
    bool covered;
public:
    card(){
        rank = 0;
        suit = 0;
        covered = true;
    }
    card(char rank, char suit, bool covered){
        this->rank = rank;
        this->suit = suit;
        this->covered = covered;
    }
    card(const card &old){
        this->rank = old.rank;
        this->suit = old.suit;
        this->covered = old.covered;
    }
    card& operator=(const card &old);
    static bool rankIsValid(char rank);
    static bool suitIsvalid(char suit);
    int rankValue(char rank);
    char getRank();
    char getSuit();
    bool getCovered();
    bool sameColorSuit(const card b);
    void setRank(char c){rank = c;}
    void setSuit(char c){suit = c;}
    void setCovered(bool c){covered = c;}
};


#endif //SOLITAIRE_CARD_H
