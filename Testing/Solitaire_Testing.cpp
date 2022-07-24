//
// Created by wende on 7/24/2022.
//
#include "../winnablefile/card.h"
#include <iostream>
#include "Solitaire_Testing.h"

int main(){
    card test1('A', 'd');
    card test2('2', 'd');

    std::cout << "Card one rank is: " << test1.getRank() << " Card suit is: " << test1.getSuit() << std::endl;
    std::cout << "Card two rank is: " << test2.getRank() << " Card suit is: " << test2.getSuit() << std::endl;
    std::cout << "Rank A is: " << test1.rankValue('A') << std::endl;
    std::cout << "Rank B is: " << test1.rankValue('B') << std::endl;
}

