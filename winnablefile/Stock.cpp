//
// Created by wendellbest on 6/9/22.
//

#include "Stock.h"

Stock Stock::getStock(std::string inputfilename) {
    Stock temp;
    std::string buffer;
    std::fstream inputfile;
    bool found = false, found2 = false;

    inputfile.open(inputfilename);
    if(inputfile.is_open()){
        while(inputfile.good()){
            std::getline(inputfile, buffer);
            if(buffer[0] == '#' || buffer[0] == '\0')
                continue;
            if(buffer.find("STOCK:") != std::string::npos)
                found = true;
            if(found == true){
                for(int i = 0; i < buffer.length() && buffer[i]!= '#'; i++){
                    if(buffer[i] == '#' || buffer[i] == 'M'){
                        found2 = true;
                        break;
                    }
                    if(buffer[i]=='|'){
                        temp.addCardToStock(Card(buffer[i], '0'));
                    }
                    else if(Card::isValidRank(buffer[i]), Card::isValidSuit(buffer[i+1])){
                        temp.addCardToStock(Card(buffer[i], buffer[i+1]));
                    }
                }
            }
            if(found2)
                break;
        }
    }
    return temp;
}

void Stock::printStock() {
    Card *ptr = sw;
    while(ptr->getRank() != 0){
        if(ptr->getRank() == '|')
            std::cout << ptr->getRank() << " ";
        else
            std::cout << ptr->getRank() << ptr->getSuit() << " ";
        ptr++;
    }
    std::cout << std::endl;
}

void Stock::addCardToStock(Card card) {
    Card *ptr = sw;
    while(ptr->getRank() != 0){
        ptr++;
    }
    *ptr=card;
}
