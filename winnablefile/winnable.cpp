//
// Created by wendellbest on 7/7/22.
//
#include <string>
#include <iostream>
#include "winnable.h"
#include "gameBoard.h"
#include "searchParameters.h"
#include "gameMovesSearch.h"

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
    //Get the command line arguments
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
    //This will run check to see if the file is valid
    std::string check = "./cmake-build-debug/check ";
    std::string argument = check + inputFileName;
    system(argument.c_str());
    //need to build the game from the file, a game is played on a board
    searchParameters search(limitedSearch, numberLimitedSearch, useHashTable, useSafeMoves, useVerboseMode);
    gameBoard game(inputFileName);
    //game.printGameBoard();
    //std::cout << game.gameInWinningConfig() << std::endl;
    gameBoard winningGame;
    gameMovesSearch movesSearch(search, game);
}