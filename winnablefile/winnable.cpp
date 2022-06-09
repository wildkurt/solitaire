//
// Created by wende on 6/7/2022.
//
#include "Testing.h"
#include "Rules.h"
#include "GameConfiguration.h"
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]){
    //Retrieve comand line flags
    //-m N : search should be limited to N moves, default value 1000
    //-c : use a hash table cache
    //-f : indicates safe moves to the foundation
    //-v : verbose mode
    bool limitMoves = false;
    int numberOfMoves = 1000;
    bool hashTable = false;
    bool safeMoves = false;
    bool verboseMode = false;
    std::string inputfilename;
    std::string buffer;
    //use for windows
    //std::string check = R"(C:\Users\wende\OneDrive\Documents\ProgrammingWork\my-c-and-c-plus-plus-projects\Solitaire\cmake-build-debug\check )";
    //use for linux
    std::string check = "./cmake-build-debug/check ";
    Testing test;
    std::fstream inputfile;
    GameConfiguration game;

    for(int i = 0;i < argc; i++){
        buffer = argv[i];
        if(buffer == "-m"){
            limitMoves = true;
            buffer = argv[++i];
            numberOfMoves = stoi(buffer);
            continue;
        }
        else if(buffer == "-c"){
            hashTable = true;
        }
        else if(buffer == "-f"){
            safeMoves = true;
        }
        else if(buffer == "-v"){
            verboseMode = true;
        }
        else if(buffer.find("winnable") == std::string::npos){
            inputfilename = buffer;
        }
    }

    game = GameConfiguration(inputfilename);

    //test.printSwitches(limitMoves,numberOfMoves,hashTable,safeMoves,verboseMode,inputfilename);
    //std::string argument = check + inputfilename;
    //system(argument.c_str());
    std::cout << "Limit: " << game.getRulesLimit() << " Turn: " << game.getRulesTurn() << std::endl;
    std::cout << "Foundation filled: ";
    game.printGameFoundation();
    std::cout << "Tableau:" << std::endl;
    game.printGameTableau();
    std::cout << "Stock:" << std::endl;
    game.printGameStock();
}
