//
// Created by wendellbest on 1/15/23.
//

#include "tableau.h"

Tableau::Tableau() {
    for(int i = 1; i <= 7; i++){
        Card *ptr = colptr(i);
        for(int i = 0; i < 27; i++){
            ptr[i] = Card();
        }
    }
}

void Tableau::addCardToTab(int col, Card card) {
    Card *ptr = colptr(col);
    while(ptr->getRank() != 0){
        ptr++;
    }
    ptr->setRank(card.getRank());
    ptr->setSuit(card.getCardSuit());
}

Card *Tableau::colptr(int col) {
    switch(col){
        case 1 : return col1;
        case 2 : return col2;
        case 3 : return col3;
        case 4 : return col4;
        case 5 : return col5;
        case 6 : return col6;
        case 7 : return col7;
        default : return nullptr;
    }
}

bool Tableau::areColumnCardsCovered() {
    for(int i = 1; i <= 7; i++){
        Card *ptr = colptr(i);
        for(int i = 0; i < 27; i++){
            if(ptr[i].isCovered())
                return true;
        }
    }
    return false;
}

