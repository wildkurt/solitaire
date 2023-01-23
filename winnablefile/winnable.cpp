//
// Created by wendellbest on 7/7/22.
//
#include <string>
#include <iostream>
#include <cstdlib>
#include "gameConfiguration.h"
#include "parseGameFile.h"

void printSettings(bool limitedSequences, int nMoves, bool useHashTable, bool useSafeMoves, bool useVerboseMode, std::string filename);
void printGame(gameConfiguration game);
/*This is the main program that will read the input from the command line
 * then start the process of building the game.*/

int main(int argc, char *argv[]){
    std::string buffer;
    std::string filename;
    std::string subString;
    std::size_t find = 0;
    bool limitedSequences = false;
    long int nMoves = 1000;
    bool useHashTable = false;
    bool useSafeMoves = false;
    bool useVerboseMode = false;
    gameConfiguration game;
    parseGameFile parser;
    //Need to get flags from command-line switches or stdin
    //stdin input
    if(argc == 1) {
        getline(std::cin, buffer);
        for(int i = 0; i < buffer.length(); i++){
            if(buffer[i] == '-'){
                if(buffer[i+1] == 'c'){
                    useHashTable = true;
                    i++; //incrementing to keep from reading as filename
                }
                else if(buffer[i+1] == 'f'){
                    useSafeMoves = true;
                    i++; //incrementing to keep from reading as filename
                }
                else if(buffer[i+1] == 'v'){
                    useVerboseMode = true;
                    i++; //incrementing to keep from reading as filename
                }
                else if(buffer[i+1] == 'm'){
                    limitedSequences = true;
                    i+=3; //incrementing in order to make substring is a number
                    for(;std::isdigit(buffer[i]);i++)
                        subString = subString + buffer[i];
                    nMoves = stoi(subString);
                }
            }
            else{
                if(filename.empty()){
                    for(;std::isalnum(buffer[i]) || std::ispunct(buffer[i]); i++)
                        filename = filename + buffer[i];
                }
            }
        }
    }
    //Command line flags
    else{
        for(int i = 0;i < argc; i++){
            buffer = argv[i];
            if(buffer == "-m"){
                limitedSequences = true;
                buffer = argv[++i];
                nMoves = stoi(buffer);
                continue;
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
                filename = buffer;
            }
        }
    }
    //for checking input settings for program
    printSettings(limitedSequences, nMoves, useHashTable, useSafeMoves, useVerboseMode, filename);

    //Need to see if the file is valid
    std::string command = "./cmake-build-debug/check ";
    command = command + filename;
    if(system(command.c_str()) != 0){
        std::cerr << "File is invalid" << std::endl;
        return 1;
    }
    //The files is valid, so need to parse the file to get the game configuration
    parser = parseGameFile(filename, game);
    game = parser.getGameFromfile();
    //Print game
    printGame(game);
}

void printSettings(bool limitedSequences, int nMoves, bool useHashTable, bool useSafeMoves, bool useVerboseMode, std::string filename){
    std::cout << std::endl;
    std::cout << "limitedSequences is: " << limitedSequences << std::endl;
    std::cout << "Number of move sequences: " << nMoves << std::endl;
    std::cout << "Hash table is: " << useHashTable << std::endl;
    std::cout << "Safe Moves is: " << useSafeMoves << std::endl;
    std::cout << "Verbose Mode is: " << useVerboseMode << std::endl;
    std::cout << "File name is: " << filename << std::endl;
    std::cout << std::endl;
}

void printGame(gameConfiguration game){
    std::cout << std::endl;
    game.getRules();
    game.getFoundation();
    game.getTableau();
    game.getStock();
    game.getMoves();
    std::cout << std::endl;
}