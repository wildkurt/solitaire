//
// Created by wendellbest on 7/7/22.
//

#include "gameRules.h"
#include <fstream>
#include <iostream>
#include <string>

gameRules::gameRules() {
    numCardsToTurnOver = 1;
    numOfWasteResets = -1;
}

gameRules::gameRules(const gameRules &old) {
    this->filename = old.filename;
    this->numCardsToTurnOver = old.numCardsToTurnOver;
    this->numOfWasteResets = old.numOfWasteResets;
}

gameRules &gameRules::operator=(const gameRules &old) {
    this->filename = old.filename;
    this->numCardsToTurnOver = old.numCardsToTurnOver;
    this->numOfWasteResets = old.numOfWasteResets;
    return *this;
}
void gameRules::getRules(std::__cxx11::basic_string<char> basicString) {
    filename = basicString;
    std::ifstream input;
    input.open(filename,std::ios_base::in);
    std::string buffer;
    bool turn = false, limits = false;
    while(std::getline(input, buffer)){
        if(buffer.find("turn") != std::string::npos){
            int pos = buffer.find_last_of("turn") + 2;
            numCardsToTurnOver = std::stoi(buffer.substr(pos,1));
            turn = true;
        }
        if(buffer.find("limit") != std::string::npos){
            int pos = buffer.find_last_of("limit") + 2;
            numOfWasteResets = std::stoi(buffer.substr(pos));
            limits = true;
        }
        if(turn == true && limits == true){
            break;
        }
    }
}

void gameRules::printRules() {
    std::cout << "The filename is: " << filename << std::endl;
    std::cout << "The number of cards to turn over is: " << numCardsToTurnOver << std::endl;
    std::cout << "The number of waste resets is: " << numOfWasteResets << std::endl;
}


