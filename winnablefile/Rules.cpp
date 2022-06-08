//
// Created by wende on 6/7/2022.
//

#include "Rules.h"

Rules::Rules() {
    turn = 0;
    limit = 0;
}

Rules Rules::findRules(const std::string& inputfilename) {
    Rules temp;
    std::fstream inputfile;
    std::string buffer;

    inputfile.open(inputfilename);
    if(inputfile.is_open()){
        while(inputfile.good()){
            std::getline(inputfile, buffer);
            if(buffer.find("limit ") != std::string::npos){
                temp.limit = std::stoi(buffer.substr(buffer.find_last_of("limit ") + 1));
            }
            else if(buffer.find("unlimited") != std::string::npos){
                temp.limit = -1;
            }
            else if(buffer.find("turn 3") != std::string::npos){
                temp.turn = 3;
            }
            else if(buffer.find("turn 1")!= std::string::npos){
                temp.turn = 1;
            }
            if(temp.turn > 0 && (temp.limit < 0 || temp.limit > 0)){
                break;
            }
        }
    }
    return temp;
}

int Rules::getTurn() {
    return turn;
}

int Rules::getLimit() {
    return limit;
}
