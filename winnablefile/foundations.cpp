//
// Created by wendellbest on 3/19/23.
//

#include <iostream>
#include <fstream>
#include "foundations.h"

void Foundations::addCard(int b, Card c) {
    fndtn[b] = c;
}

void Foundations::printFoundations() {
    std::cout << "FOUNDATIONS:" << std::endl;
    for(int i = 0; i < 4; i++)
        std::cout << fndtn[i].getRank() << fndtn[i].getSuit() << " ";
    std::cout << std::endl;
}

void Foundations::getCardValues(Card *pCard) {
    for(int i = 0; i < 4; i++){
        pCard[i] = fndtn[i];
    }
}

void Foundations::printFoundations(std::ofstream *file) {
    *file << "FOUNDATIONS:" << std::endl;
    for(int i = 0; i < 4; i++)
        *file << fndtn[i].getRank() << fndtn[i].getSuit() << " ";
    *file << std::endl;
}
