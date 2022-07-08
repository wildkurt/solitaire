//
// Created by wende on 6/7/2022.
//

#include "Tableau.h"
#include <fstream>
#include <iostream>

Tableau::Tableau(const Tableau &tableau) {
    for(int i = 0; i < 30; i++){
        this->t7[i] = tableau.t7[i];
        this->t6[i] = tableau.t6[i];
        this->t5[i] = tableau.t5[i];
        this->t4[i] = tableau.t4[i];
        this->t3[i] = tableau.t3[i];
        this->t2[i] = tableau.t2[i];
        this->t1[i] = tableau.t1[i];
    }
}

Tableau &Tableau::operator=(const Tableau &tableau) {
    for(int i = 0; i < 30; i++){
        this->t7[i] = tableau.t7[i];
        this->t6[i] = tableau.t6[i];
        this->t5[i] = tableau.t5[i];
        this->t4[i] = tableau.t4[i];
        this->t3[i] = tableau.t3[i];
        this->t2[i] = tableau.t2[i];
        this->t1[i] = tableau.t1[i];
    }
    return *this;
}

Tableau Tableau::getTableau(std::string inputfilename) {
    Tableau temp;
    bool found1 = false, covered = true;
    std::string buffer;
    std::fstream inputfile;
    int col = 7;

    inputfile.open(inputfilename);
    if(inputfile.is_open()){
        while(inputfile.good()){
            std::getline(inputfile, buffer);
            if(buffer[0] == '#' || buffer[0] == '\0')
                continue;
            if(buffer.find("TABLEAU:") != std::string::npos){
                std::getline(inputfile, buffer);
                found1 = true;
            }
            if(buffer.find("STOCK:") != std::string::npos)
                break;
            if(found1 && col != 0){
                for(long i = 0; i < buffer.length() && buffer[i] != '#'; i++){
                    if(Card::isValidRank(buffer[i]) && Card::isValidSuit(buffer[i+1])){
                        Card card(buffer[i],buffer[i+1], covered);
                        temp.addCardToCol(card, col);
                    }
                    else if(buffer[i] == '|'){
                        covered = false;
                        Card card(buffer[i], '0', covered);
                        temp.addCardToCol(card, col);
                    }
                }
                col--;
                covered = true;
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

bool Tableau::anyCoveredCards() {
    bool result = false;
    Card *ptr;
    for(int i = 1; i < 8; i++){
        ptr = getColPtr(i);
        while(ptr->getRank() != 0){
            if(ptr->isCovered() == true){
                result = true;
                break;
            }
            ptr++;
        }
        if(result == true)
            break;
    }
    return result;
}
