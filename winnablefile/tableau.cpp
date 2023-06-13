//
// Created by wendellbest on 3/19/23.
//

#include <iostream>
#include <fstream>
#include "tableau.h"

Card *Tableau::getColPointer(int c) {
    switch(c){
        case 7 : return col7;
        case 6 : return col6;
        case 5 : return col5;
        case 4 : return col4;
        case 3 : return col3;
        case 2 : return col2;
        case 1 : return col1;
        default : return nullptr;
    }
}

void Tableau::addCardToColumn(int c, Card d) {
    Card *ptr = getColPointer(c);
    while(ptr->getRank()!='0'){ptr++;}
    *ptr = d;
    if(d.checkIfCardIsCovered())
        numberOfCovered += 1;
}

void Tableau::printTableau() {
    int col = 7;
    Card *ptr = getColPointer(col);
    std::cout << "TABLEAU:" << std::endl;
    while(col > 0){
        for(int i = 0; i< TABSIZE ; i++){
            if((ptr + i)->getRank() == '|')
                std::cout << (ptr + i)->getRank() << " ";
            else if((ptr + i)->getRank() != '0')
                std::cout << (ptr + i)->getRank() << (ptr + i)->getSuit() << " ";
        }
        col--;
        ptr = getColPointer(col);
        std::cout << std::endl;
    }
}

bool Tableau::anyCoveredCards() {
    if(numberOfCovered == 0)
        return false;
    else
        return true;
}
