//
// Created by wendellbest on 7/7/22.
//

#include "gameStock.h"
#include <fstream>
#include <iostream>

void gameStock::getStock(std::__cxx11::basic_string<char> basicString) {
    filename = basicString;
    std::ifstream input;
    input.open(filename, std::ios_base::in);
    std::string buffer;
    bool stckFound = false;

    while(std::getline(input, buffer)){
        if(buffer[0] == '#'){
            continue;
        }
        if(buffer.find("STOCK:") != std::string::npos){
            stckFound = true;
        }
        if(buffer.find("MOVES:") != std::string::npos){
            break;
        }
        if(stckFound){
            for(int i = 0; i < buffer.size(); i++){
                if(card::rankIsValid(buffer[i]) && card::suitIsvalid(buffer[i+1])){
                    card temp(buffer[i], buffer[i+1]);
                    sw.push_back(temp);
                }
                if(buffer[i] == '|'){
                    card temp('|', 0);
                    sw.push_back(temp);
                }
            }
        }
    }
}

void gameStock::printStock() {
    std::cout << "The Stock/Waste is: " << std::endl;
    for(int i = 0; i < sw.size(); i++){
        if(sw[i].getRank() != '|')
            std::cout << sw[i].getRank() << sw[i].getSuit() << " ";
        else
            std::cout << sw[i].getRank() << " ";
    }
    std::cout << std::endl;
}
