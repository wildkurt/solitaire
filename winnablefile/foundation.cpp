//
// Created by wendellbest on 1/15/23.
//

#include <iostream>
#include "foundation.h"
int indexOfSuit(char c){
    switch(c){
        case 'c' : return 0;
        case 'd' : return 1;
        case 'h' : return 2;
        case 's' : return 3;
        default : return 0;
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
Foundation::Foundation(const Foundation &fndtn) {
    for(int i = 0; i < 4; i++){
        farr[i] = fndtn.farr[i];
    }
}

Foundation &Foundation::operator=(const Foundation &fndtn) {
    for(int i = 0; i < 4; i++){
        farr[i] = fndtn.farr[i];
    }
    return *this;
}

Card Foundation::getCard(int i) {
    return farr[i];
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

void Foundation::printFoundations() {
    std::cout << "Clubs: " << farr[0].getRank() << farr[0].getCardSuit()<< std::endl;
    std::cout << "Diamonds: " << farr[1].getRank() << farr[1].getCardSuit()<< std::endl;
    std::cout << "Hearts: " << farr[2].getRank() << farr[2].getCardSuit()<< std::endl;
    std::cout << "Spades: " << farr[3].getRank() << farr[3].getCardSuit()<< std::endl;

}





