//
// Created by wendellbest on 5/19/22.
//

#ifndef SOLITAIRE_CARDHEADER_H
#define SOLITAIRE_CARDHEADER_H



class Card{
private:
    char rank;
    char suit;
    bool covered;
public:
    Card(){rank = '_'; suit = '_', covered = false;}
    Card(char r, char s, bool c){rank = r; suit = s; covered = c;}
    Card(Card &p);
    Card(const Card &p);
    Card& operator=(Card *p);
    char getRank(){return rank;}
    char getSuit(){return suit;}
    bool getCovered(){return covered;}
    void setRank(char c){rank = c;}
    void setSuit(char c){suit = c;}
    void setCovered(bool c){covered = c;}
    int getRankValue(){return rankValue(rank);}
    int rankValue(char c);
};

#endif //SOLITAIRE_CARDHEADER_H
