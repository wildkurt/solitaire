//
// Created by wendellbest on 7/7/22.
//

#include "gameFoundations.h"
#include <fstream>
#include <iostream>

void gameFoundations::getFoundation(std::__cxx11::basic_string<char> basicString) {
    filename = basicString;
    std::ifstream input;
    input.open(filename,std::ios_base::in);
    std::string buffer;
    bool fndFound = false;
    int index = 0;
    while(std::getline(input, buffer)){
        if(buffer[0] == '#'){
            continue;
        }
        //find foundations, the cards could follow the heading
        if(buffer.find("FOUNDATIONS:") != std::string::npos){
            fndFound = true;
            for(int i = buffer.find_last_of("FOUNDATIONS:"); i < buffer.size(); i++){
                if((card::rankIsValid(buffer[i]) || buffer[i] == '_') && card::suitIsvalid(buffer[i + 1])){
                    fnd[index].setRank(buffer[i]);
                    fnd[index].setSuit(buffer[i+1]);
                    index++;
                }
            }
            std::getline(input,buffer);
        }
        //The foundations are below the foundation heading in a row or col
        if(fndFound == true){
            for(int i = 0; i < buffer.size(); i++){
                if(buffer[i] == '#'){
                    break;
                }
                if((card::rankIsValid(buffer[i]) || buffer[i] == '_') && card::suitIsvalid(buffer[i + 1])){
                    fnd[index].setRank(buffer[i]);
                    fnd[index].setSuit(buffer[i+1]);
                    index++;
                }
            }
        }
        //Stop reading lines if the tableau is found
        if(buffer.find("TABLEAU:") != std::string::npos){
            break;
        }
    }
}
