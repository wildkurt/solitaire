//
// Created by wendellbest on 7/7/22.
//
#include <string>
#include <iostream>
#include "winnable.h"
#include "card.h"

/*This is the main program that will read the input from the command line
 * then start the process of building the game.*/

int main(int argc, char *argv[]){
    std::string buffer;
    bool limitedSearch = false;
    long int numberLimitedSearch = 1000;
    bool useHashTable = false;
    bool useSafeMoves = false;
    bool useVerboseMode = false;
    std::string inputFileName;

    for(int i = 0; i < argc; i++){
        buffer = argv[i];
        if(buffer == "-m"){
            limitedSearch = true;
            buffer = argv[++i];
            numberLimitedSearch = stoi(buffer);
        }
        else if(buffer == "-c"){
            useHashTable = true;
        }
        else if(buffer == "-f"){
            useSafeMoves = true;
        }
        else if(buffer == "-v"){
            useVerboseMode = true;
        }
        else if(buffer.find("winnable") == std::string::npos){
            inputFileName = buffer;
        }
    }
    std::cout << "Limited Search is: " << limitedSearch << std::endl;
    std::cout << "Limited Search Number is: " << numberLimitedSearch << std::endl;
    std::cout << "Hash Table is: " << useHashTable << std::endl;
    std::cout << "Safe Moves is: " << useSafeMoves << std::endl;
    std::cout << "Verbos Mode is: " << useVerboseMode << std::endl;
    std::cout << "File name is: " << inputFileName << std::endl;
    std::cout << std::endl;
    std::string check = "./cmake-build-debug/check ";
    std::string argument = check + inputFileName;
    system(argument.c_str());


}