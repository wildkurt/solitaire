//
// Created by wendellbest on 7/7/22.
//

#include "gameTableau.h"
#include <fstream>
#include <iostream>

void gameTableau::getTableau(std::__cxx11::basic_string<char> basicString) {
    filename = basicString;
    std::ifstream input;
    input.open(filename,std::ios_base::in);
    std::string buffer;
    bool tabFound = false;
    int columns = 7;

    while(std::getline(input, buffer)){
        if(buffer[0] == '#'){
            continue;
        }
        if(buffer.find("TABLEAU:") != std::string::npos){
            tabFound = true;
            //The tableau is always below the "TABLEAU:" heading
            continue;
        }
        if(tabFound == true){
            for(int i = 0; i < buffer.size(); i++){
                if(card::rankIsValid(buffer[i]) && card::suitIsvalid(buffer[i+1])){
                    card temp(buffer[i], buffer[i+1]);
                    addCardsToColumn(columns, temp);
                }
                if(buffer[i] == '|'){
                    card temp('|', 0);
                    addCardsToColumn(columns, temp);
                }
            }
            if(columnFilled(columns)){
                columns--;
            }
        }
    }
}

void gameTableau::printTableau() {
    std::cout << "The Tableau is: " << std::endl;
    for(int i = 7 ; i >= 1; i--){
        printColumn(i);
        std::cout << std::endl;
    }
}

void gameTableau::addCardsToColumn(int columns, card newCard) {
    switch(columns){
        case 7 : col7.push_back(newCard); break;
        case 6 : col6.push_back(newCard); break;
        case 5 : col5.push_back(newCard); break;
        case 4 : col4.push_back(newCard); break;
        case 3 : col3.push_back(newCard); break;
        case 2 : col2.push_back(newCard); break;
        case 1 : col1.push_back(newCard); break;
        default : break;
    }
}

bool gameTableau::columnFilled(int columns) {

    switch(columns){
        case 7 : if(!col7.empty()) return true;
        case 6 : if(!col6.empty()) return true;
        case 5 : if(!col5.empty()) return true;
        case 4 : if(!col4.empty()) return true;
        case 3 : if(!col3.empty()) return true;
        case 2 : if(!col2.empty()) return true;
        case 1 : if(!col1.empty()) return true;
        default: return false;
    }
}

void gameTableau::printColumn(int i) {
    std::vector <card> ptr = getColPtr(i);
    for(int i = 0; i < ptr.size(); i++){
        if(ptr[i].getRank() != '|')
            std::cout << ptr[i].getRank() << ptr[i].getSuit() << " ";
        else
            std::cout << ptr[i].getRank() << " ";
    }
}

std::vector<card> gameTableau::getColPtr(int i) {
    switch(i){
        case 7 : return col7;
        case 6 : return col6;
        case 5 : return col5;
        case 4 : return col4;
        case 3 : return col3;
        case 2 : return col2;
        case 1 : return col1;
        default : nullptr;
    }
}


