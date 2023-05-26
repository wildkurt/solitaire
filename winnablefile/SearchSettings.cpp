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
    //Reading from STDIN
    if(number <=1){
        std::string input = "";
        std::getline(std::cin, input);
        std::string::iterator it = input.begin();
        for(;it != input.end(); it++){
            if(*it == '-'){
                switch(*(it+1)){
                    case 'm' : limitedMoves = true; it++; break;
                    case 'c' : useHashtable = true; it++; break;
                    case 'f' : useSafeMoves = true; it++; break;
                    case 'v' : useVerboseMode = true; it++; break;
                }
            }
            else if(isdigit(*it) && limitedMoves){
                if(*(it-3) == '-' && *(it-2) == 'm'){
                    std::string number = "";
                    while(isdigit(*it)){
                        number.push_back(*it);
                        if(it+1 != input.end())
                            it++;
                        else
                            break;
                    }
                    numberOfLimitedMoves = stoi(number);
                }
            }
            else if(*it != ' '){
                std::string namefile = "";
                do{
                    if(*it != '-')
                    namefile.push_back(*it);
                    if(it + 1 == input.end())
                        break;
                    it++;
                }while(isalnum(*it) || std::ispunct(*it));
                filename = namefile;
            }
        }
    }
    //reading from command line
    else{
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
    }
}


