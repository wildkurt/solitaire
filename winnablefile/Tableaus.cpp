//
// Created by wendellbest on 5/19/22.
//

#include "Tableaus.h"
#include <iostream>

Tableaus::Tableaus() {
    column1Filled = false;
    column2Filled = false;
    column3Filled = false;
    column4Filled = false;
    column5Filled = false;
    column6Filled = false;
    column7Filled = false;
}

bool Tableaus::addCardToTableau(Card c, int col) {
    switch(col){
        case 1 : col1.push_back(c); return true;
        case 2 : col2.push_back(c); return true;
        case 3 : col3.push_back(c); return true;
        case 4 : col4.push_back(c); return true;
        case 5 : col5.push_back(c); return true;
        case 6 : col6.push_back(c); return true;
        case 7 : col7.push_back(c); return true;
        default : return false;
    }
}

bool Tableaus::isColumnFilled(int i){
    bool result = false;
    switch (i){
        case 1 : result = column1Filled; break;
        case 2 : result = column2Filled; break;
        case 3 : result = column3Filled; break;
        case 4 : result = column4Filled; break;
        case 5 : result = column5Filled; break;
        case 6 : result = column6Filled; break;
        case 7 : result = column7Filled; break;
        default : return false;
    }
    return result;
}

void Tableaus::columnFilled(int i) {
    switch(i){
        case 7 : column7Filled = true; break;
        case 6 : column6Filled = true; break;
        case 5 : column5Filled = true; break;
        case 4 : column4Filled = true; break;
        case 3 : column3Filled = true; break;
        case 2 : column2Filled = true; break;
        case 1 : column1Filled = true; break;
    }
}

Card Tableaus::getCard(int index, int col) {
    switch(col){
        case 7 : return col7.at(index);
        case 6 : return col6.at(index);
        case 5 : return col5.at(index);
        case 4 : return col4.at(index);
        case 3 : return col3.at(index);
        case 2 : return col2.at(index);
        case 1 : return col1.at(index);
    }
}

int Tableaus::getTableauColSize(int i) {
    int size = 0;
    switch(i){
        case 7 : size = col7.size(); break;
        case 6 : size = col6.size(); break;
        case 5 : size = col5.size(); break;
        case 4 : size = col4.size(); break;
        case 3 : size = col3.size(); break;
        case 2 : size = col2.size(); break;
        case 1 : size = col1.size(); break;
    }
    return size;
}



