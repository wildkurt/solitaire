//
// Created by wende on 6/7/2022.
//

#include "Foundation.h"
#include <fstream>
#include <iostream>

Foundation::Foundation(Foundation &foundation) {
    for(int i = 0; i < 4; i++){
        this->fd[i] = foundation.fd[i];
    }
}

Foundation &Foundation::operator=(const Foundation &foundation) {
    for(int i = 0; i < 4; i++){
        this->fd[i] = foundation.fd[i];
    }
    return *this;
}

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
    bool found = false, covered = false;
    std::string buffer;
    std::fstream inputfile;
    Foundation temp;

    inputfile.open(inputfilename);
    if(inputfile.is_open()){
        while(inputfile.good() && !isFoundationFilled()){
            std::getline(inputfile,buffer);
            if(buffer.find("FOUNDATIONS:") != std::string::npos) {
                found = true;
                std::getline(inputfile,buffer);
            }
            if(found == true){
                for(int i = 0; i < buffer.length(); i++){
                    if(isFoundationFilled()){
                        break;
                    }
                    if(buffer[i] == '_' && Card::isValidSuit(buffer[i+1])){
                        Card card(buffer[i], buffer[i+1], covered);
                        temp.addCardToFoundation(card);
                    }
                    else{
                        if(Card::isValidRank(buffer[i]) && Card::isValidSuit(buffer[i+1])){
                            Card card(buffer[i], buffer[i++], covered);
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

void Foundation::printFoundation() {
    for(int i = 0; i < 4; i++){
        std::cout << fd[i].getRank() << fd[i].getSuit() <<" ";
    }
    std::cout << std::endl;
}



