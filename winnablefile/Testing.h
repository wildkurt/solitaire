//
// Created by wende on 6/7/2022.
//

#ifndef SOLITAIRE_TESTING_H
#define SOLITAIRE_TESTING_H
#include <string>

class Testing {
public:
    Testing()=default;
    void printSwitches(bool limitMoves, int numberOfMoves, bool hashTable, bool safeMoves, bool verboseMode, std::string filename );
};


#endif //SOLITAIRE_TESTING_H
