//
// Created by wendellbest on 3/18/23.
//

#include <iostream>
#include "SearchSettings.h"

SearchSettings::SearchSettings() {
    limitedMoves = false;
    numberOfLimitedMoves = 1000;
    useHashtable = false;
    useSafeMoves = false;
    useVerboseMode = false;
}

void SearchSettings::getSettingsFromCL(int number, char **arr) {
    for(int i = 1; i < number ; i++){
        std::string variable = arr[i];
        if(variable.find("-m") != std::string::npos){
            limitedMoves = true;
            variable = arr[i+1];
            numberOfLimitedMoves = stoi(variable);
            i++;
        }
        else if(variable.find("-c") != std::string::npos)
            useHashtable = true;
        else if(variable.find("-f") != std::string::npos)
            useSafeMoves = true;
        else if(variable.find("-v") != std::string::npos)
            useVerboseMode = true;
        else
            filename = arr[i];
    }
    std::cout << std::endl;
}

void SearchSettings::printSettingsFromCL() {
    std::cout << "limitedMoves: " << limitedMoves << std::endl;
    std::cout << "numberOfLimitedMoves: " << numberOfLimitedMoves << std::endl;
    std::cout << "useHashtable: " << useHashtable << std::endl;
    std::cout << "useSafeMoves: " << useSafeMoves << std::endl;
    std::cout << "useVerboseMode: " << useVerboseMode << std::endl;
    std::cout << "filename: " << filename << std::endl;
}

