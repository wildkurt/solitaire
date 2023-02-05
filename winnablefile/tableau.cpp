//
// Created by wendellbest on 1/15/23.
//

#include <iostream>
#include "tableau.h"

Tableau::Tableau() {
    for(int i = 1; i <= 7; i++){
        Card *ptr = colptr(i);
        for(int i = 0; i < 27; i++){
            ptr[i] = Card();
        }
    }
}

Tableau::Tableau(const Tableau &tab) {
    for(int i = 0; i < 27; i++){
        col1[i] = tab.col1[i];
        col2[i] = tab.col2[i];
        col3[i] = tab.col3[i];
        col4[i] = tab.col4[i];
        col5[i] = tab.col5[i];
        col6[i] = tab.col6[i];
        col7[i] = tab.col7[i];
    }
}

Tableau &Tableau::operator=(const Tableau &tab) {
    for (int i = 0; i < 27; i++) {
        col1[i] = tab.col1[i];
        col2[i] = tab.col2[i];
        col3[i] = tab.col3[i];
        col4[i] = tab.col4[i];
        col5[i] = tab.col5[i];
        col6[i] = tab.col6[i];
        col7[i] = tab.col7[i];
    }
    return *this;
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

void Tableau::printTableaus() {
    for(int i = 7; i > 0; i--){
        Card *ptr = colptr(i);
        std::cout << "Tableau " << i << ": ";
        while(ptr->getRank()!=0){
            if(ptr->getRank() == '|')
                std::cout << ptr->getRank() << " ";
            else
                std::cout << ptr->getRank() << ptr->getCardSuit() << " ";
            ptr++;
        }
        std::cout << std::endl;
    }
}




