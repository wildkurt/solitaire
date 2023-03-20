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
}

void Tableau::printTableau(std::ofstream *file) {
    int col = 7;
    Card *ptr = getColPointer(col);
    *file << "TABLEAU:" << std::endl;
    while(col > 0){
        for(int i = 0; i< TABSIZE ; i++){
            if((ptr + i)->getRank() == '|')
                *file << (ptr + i)->getRank() << " ";
            else if((ptr + i)->getRank() != '0')
                *file << (ptr + i)->getRank() << (ptr + i)->getSuit() << " ";
        }
        col--;
        ptr = getColPointer(col);
        *file << std::endl;
    }
}
