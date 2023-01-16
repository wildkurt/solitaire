//
// Created by wendellbest on 1/15/23.
//

#include "foundation.h"
int indexOfSuit(char c){
    switch(c){
        case 'c' : return 0;
        case 'd' : return 1;
        case 'h' : return 2;
        case 's' : return 3;
    }
}
Foundation::Foundation() {
    farr[0].setRank('_');
    farr[0].setSuit('c');
    farr[1].setRank('_');
    farr[1].setSuit('d');
    farr[2].setRank('_');
    farr[2].setSuit('h');
    farr[3].setRank('_');
    farr[3].setSuit('s');
}

bool Foundation::isSafeToMoveCard(Card card) {
    for(int i = 0; i < 4; i++){
        if(farr[i].getRankValue(farr[i].getRank())+1 < card.getRankValue(card.getRank()))
            return false;
    }
    return true;
}

void Foundation::addCardToFoundation(Card card) {
    farr[indexOfSuit(card.getCardSuit())].setRank(card.getRank());
    farr[indexOfSuit(card.getCardSuit())].setSuit(card.getCardSuit());
}
