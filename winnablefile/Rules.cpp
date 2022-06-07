//
// Created by wendellbest on 6/6/22.
//

#include <iostream>
#include <fstream>
#include <string>
#include "Rules.h"

Rules::Rules() {
    turnover = 0;
    limit = 0;
}

void Rules::setTurnOver(std::string turnover) {
    if(turnover.find("turn 3"))
        turnover = 3;
    else
        turnover = 1;
}

void Rules::setLimit(std::string limit) {
    if(limit.find("limit "))
        this->limit = std::stoi(limit);
}

int Rules::findRules(std::string filename) {
    std::string buffer;
    std::ifstream inputfile;
    inputfile.open(filename);
    if(inputfile.is_open()){
        while(inputfile.good() && limit == 0 && turnover == 0){
            std::getline(inputfile,buffer);
            if(buffer.find("turn")){
                this->setTurnOver(buffer.substr(buffer.find("turn")));
            }
            if(buffer.find("limit")){
                this->setLimit(buffer.substr(buffer.find("limit")));
            }
        }
        return 0;
    }
    return 1;
}
