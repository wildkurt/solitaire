//
// Created by wende on 6/7/2022.
//

#include "Rules.h"

Rules::Rules() {
    turn = 0;
    limit = 0;
}

Rules::Rules(const Rules &rules) {
    this->turn = rules.turn;
    this->limit = rules.limit;
}

Rules &Rules::operator=(const Rules &rules) {
    this->turn = rules.turn;
    this->limit = rules.limit;
    return *this;
}

Rules Rules::findRules(const std::string& inputfilename) {
    Rules temp;
    std::fstream inputfile;
    std::string buffer;

    inputfile.open(inputfilename);
    if(inputfile.is_open()){
        while(inputfile.good()){
            std::getline(inputfile, buffer);
            if(buffer[0] == '#' || buffer[0] == '\0')
                continue;
            if(buffer.find("limit ") != std::string::npos){
                int endLimit = buffer.find_first_of("limit") + 5;
                int endNumber = buffer.find_first_of('#');
                if(endNumber == 0)
                    endNumber = buffer.find_first_of('\0');
                std::string sudtemp = buffer.substr(endLimit, endNumber - endLimit);
                temp.limit = std::stoi(sudtemp);
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


