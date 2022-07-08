//
// Created by wendellbest on 6/9/22.
//

#include "Stock.h"

Stock::Stock(const Stock &stock) {
    for(int i = 0; i < 30; i++){
        this->sw[i] = stock.sw[i];
    }
}

Stock &Stock::operator=(const Stock &stock) {
    for(int i = 0; i < 30; i++){
        this->sw[i] = stock.sw[i];
    }
    return *this;
}

Stock Stock::getStock(std::string inputfilename) {
    Stock temp;
    std::string buffer;
    std::fstream inputfile;
    bool found = false, found2 = false, covered = false;

    inputfile.open(inputfilename);
    if(inputfile.is_open()){
        while(inputfile.good()){
            std::getline(inputfile, buffer);
            if(buffer[0] == '#' || buffer[0] == '\0')
                continue;
            if(buffer.find("STOCK:") != std::string::npos)
                found = true;
            if(found == true){
                for(long i = 0; i < buffer.length() && buffer[i]!= '#'; i++){
                    if(buffer[i] == '#' || buffer[i] == 'M'){
                        found2 = true;
                        break;
                    }
                    if(buffer[i]=='|'){
                        Card card(buffer[i], '0', covered);
                        temp.addCardToStock(card);
                        covered = true;
                    }
                    else if(Card::isValidRank(buffer[i]), Card::isValidSuit(buffer[i+1])){
                        Card card(buffer[i], buffer[i+1], covered);
                        temp.addCardToStock(card);
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

bool Stock::isStockEmptyAndOneWasteCard() {
    bool result = false;
    if(sw[0].getRank() == '|' && sw[1].getRank() == 0)
        result = true;
    else if(Card::isValidRank(sw[0].getRank()) && sw[1].getRank() == '|' && sw[2].getRank() == 0)
        result = true;
    return result;
}

