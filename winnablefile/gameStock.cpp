//
// Created by wendellbest on 7/7/22.
//

#include "gameStock.h"
#include <fstream>
#include <iostream>

gameStock::gameStock(const gameStock &old) {
    this->sw = old.sw;
    this->filename = old.filename;
}

gameStock &gameStock::operator=(const gameStock &old) {
    this->sw = old.sw;
    this->filename = old.filename;
    return *this;
}

void gameStock::getStock(std::__cxx11::basic_string<char> basicString) {
    filename = basicString;
    std::ifstream input;
    input.open(filename, std::ios_base::in);
    std::string buffer;
    bool stckFound = false;
    bool covered = false;
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
                    card temp(buffer[i], buffer[i+1], covered);
                    sw.push_back(temp);
                }
                if(buffer[i] == '|'){
                    covered = true;
                    card temp('|', 0, covered);
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

bool gameStock::winningConfigStock() {
    bool result = true;
    for(int i = 0; i < sw.size(); i++){
        if(sw[i].getCovered() == true) {
            result = false;
            break;
        }
    }
    if(sw.size() > 3){
        result = false;
    }
    return result;
}


