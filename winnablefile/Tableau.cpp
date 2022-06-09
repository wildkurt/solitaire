//
// Created by wende on 6/7/2022.
//

#include "Tableau.h"
#include <fstream>
#include <iostream>

Tableau Tableau::getTableau(std::string inputfilename) {
    Tableau temp;
    bool found1 = false;
    std::string buffer;
    std::fstream inputfile;
    int col = 7;

    inputfile.open(inputfilename);
    if(inputfile.is_open()){
        while(inputfile.good()){
            std::getline(inputfile, buffer);
            if(buffer.find("TABLEAU:") != std::string::npos){
                std::getline(inputfile, buffer);
                found1 = true;
            }
            if(buffer.find("STOCK:") != std::string::npos || col == 0)
                break;
            if(found1){
                for(int i = 0; i < buffer.length(); i++){
                    if(Card::isValidRank(buffer[i]) && Card::isValidSuit(buffer[i+1]))
                        temp.addCardToCol(Card(buffer[i], buffer[i+1]), col);
                    else if(buffer[i] == '|')
                        temp.addCardToCol(Card(buffer[i], '0'), col);
                }
                col--;
            }
            if(col == 0)
                break;
        }
    }
    return temp;
}

void Tableau::addCardToCol(Card card, int col) {
    Card *ptr;
    ptr = getColPtr(col);
    while(ptr->getRank() != 0){
        ptr++;
    }
    *ptr = card;
}

Card *Tableau::getColPtr(int c) {
    Card *ptr;
    switch(c){
        case 1 : ptr = t1; break;
        case 2 : ptr = t2; break;
        case 3 : ptr = t3; break;
        case 4 : ptr = t4; break;
        case 5 : ptr = t5; break;
        case 6 : ptr = t6; break;
        case 7 : ptr = t7; break;
        default: ptr = nullptr;
    }
    return ptr;
}

void Tableau::printTableau() {
    Card *ptr;
    for(int i = 7; i >= 1; i--){
        ptr = getColPtr(i);
        while(ptr->getRank() != 0){
            if(ptr->getRank() == '|')
                std::cout << ptr->getRank() << " ";
            else
                std::cout << ptr->getRank() << ptr->getSuit() << " ";
            ptr++;
        }
        std::cout << std::endl;
    }
}
