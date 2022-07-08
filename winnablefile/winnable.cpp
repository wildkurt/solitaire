//
// Created by wende on 6/7/2022.
//
#include "Testing.h"
#include "Rules.h"
#include "GameConfiguration.h"
#include "winnable.h"
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
    GameConfiguration game(inputfilename);
    game.printGameTableau();
    winnable winner(limitMoves, numberOfMoves, hashTable, safeMoves, verboseMode);
    game = winner.findWinningMoves(game);
}
