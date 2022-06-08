//
// Created by wende on 6/7/2022.
//

#include "Foundation.h"
#include <fstream>

void Foundation::addCardToFoundation(Card card) {
    if(card.getSuit() == 'c'){
        fd[0] = card;
    }
    else if(card.getSuit() == 'd'){
        fd[1] = card;
    }
    else if(card.getSuit() == 'h'){
        fd[2] = card;
    }
    else if(card.getSuit() == 's'){
        fd[3] = card;
    }
}

Foundation Foundation::getFoundation(std::string inputfilename) {
    bool result = false, found = false;
    std::string buffer;
    std::fstream inputfile;
    Foundation temp;

    inputfile.open(inputfilename);
    if(inputfile.is_open()){
        while(inputfile.good() && !isFoundationFilled()){
            std::getline(inputfile,buffer);
            if(buffer.find("FOUNDATION:") != std::string::npos) {
                found = true;
                std::getline(inputfile,buffer);
            }
            if(found == true){
                for(int i = 0; i < buffer.length(); i++){
                    if(isFoundationFilled()){
                        break;
                    }
                    if(buffer[i] == '_' && Card::isValidSuit(buffer[i+1])){
                        Card card(buffer[i], buffer[i+1]);
                        temp.addCardToFoundation(card);
                    }
                    else{
                        if(Card::isValidRank(buffer[i]) && Card::isValidSuit(buffer[i+1])){
                            Card card(buffer[i], buffer[i++]);
                            temp.addCardToFoundation(card);
                        }
                    }
                }
            }
        }
    }
    return temp;
}

bool Foundation::isFoundationFilled() {
    bool result = false;
    for(int i = 0; i < 4; i++){
        if(fd[i].getRank() == '_' || Card::isValidRank(fd[i].getRank()))
            result = true;
        else{
            result = false;
            break;
        }
    }
    return result;
}

Foundation::Foundation(Foundation &foundation) {
    for(int i = 0; i < 4; i++){
        this->fd[i] = foundation.fd[i];
    }
}

