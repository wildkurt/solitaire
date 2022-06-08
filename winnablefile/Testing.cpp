//
// Created by wende on 6/7/2022.
//

#include <iostream>
#include <string>
#include "Testing.h"

void Testing::printSwitches(bool limitMoves, int numberOfMoves, bool hashTable, bool safeMoves, bool verboseMode, std::string filename ){
    std::cout << "Limit Moves: " << limitMoves << std::endl;
    std::cout << "Number of moves: " << numberOfMoves << std::endl;
    std::cout << "Hash Table: " << hashTable << std::endl;
    std::cout << "Safe Moves: " << safeMoves << std::endl;
    std::cout << "Verbose Mode: " << verboseMode << std::endl;
    std::cout << "Input file name: " << filename << std::endl;
}