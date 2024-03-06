//
// Created by wendellbest on 3/5/24.
//
#include <iostream>
#include <string>
#include <cstring>
#include "winnable.h"

Winnable::Winnable() {
    limitmoves = false;
    movestoplay = 1000;
    useHashTable = false;
    foundationSafeMoves = false;
    verboseMode = false;
    inputfile = "";
    game = {.rules = {.wasteResets = 0, .cardTurnover = 0}, .foundation = {.foundation = {0}}, .tableau ={.tab1 = {0},
          .tab2 = {0}, .tab3 = {0}, .tab4 = {0}, .tab5 = {0}, .tab6 = {0}, .tab7 = {0}}, .stockwaste = {.sw = {0}}};
}

bool Winnable::getLimitedMoves(){return limitmoves;}
int Winnable::getMovestoPlay(){return movestoplay;}
bool Winnable::getUseHashTable(){return useHashTable;}
bool Winnable::getFoundationSafeMoves(){return foundationSafeMoves;}
bool Winnable::getVerboseMode(){return verboseMode;}
std::string Winnable::getInputFileName(){return inputfile;}

void Winnable::retrieveCommandLineArguments(int args, char **argv) {
    for(int i = 0; i < args ; i++){
        std::string v(argv[i]);
        if(v == "-m"){
            this->limitmoves = true;
            std::string num(argv[++i]);
            this->movestoplay = stoi(num);
        }
        else if(v == "-c"){
            this->useHashTable = true;
        }
        else if(v == "-f"){
            this->foundationSafeMoves = true;
        }
        else if(v == "-v"){
            this->verboseMode = true;
        }
        else if(!v.empty()){
            this->inputfile = v;
        }
    }
}

bool Winnable::getAndCheckGameFile() {
    // There could be a file name given, or it is coming from stdin
    // Using Advance will check the file and write the file to a clean exchange format, unless the file is invalid.
    // The process will be to run Advance then if the file is valid, then get the Game Configuration from the file
    char buffer[MAX_BUFFER] = {0};
    std::string command = "./advance -o exchange.txt ", result, inputfromAdvance = "exchange.txt";
    FILE *advancePTR, *getGF;
    int index = 0;

    if(this->inputfile.empty()){
        //Run Advance without a file name
        advancePTR = popen(command.c_str(), "r");
    }
    else{
        //Run advance with a file name
        command.append(this->inputfile);
        advancePTR = popen(command.c_str(), "r");
    }
    if(advancePTR == NULL){
        std::cerr << "File " << this->inputfile << " not found." << std::endl;
        return false;
    }
    fgets(buffer, MAX_BUFFER, advancePTR);

    result = buffer;

    index = result.find("moves, all valid");

    if(!index){
        return false;
    }
    else{
        char *filename = (char *)inputfromAdvance.c_str();
        getTheGameConfigFromFile(&this->game, filename);
    }

    return true;
}

void Winnable::printWinnableCLIArguments() {
    std::cout << "Limited moves set to: " << this->limitmoves << " The limit is: " << this->movestoplay << std::endl;
    std::cout << "Use a hash table set to: " << this->useHashTable << std::endl;
    std::cout << "Foundation safe moves are: " << this->foundationSafeMoves << std::endl;
    std::cout << "Verbose mode is: " << this->verboseMode << std::endl;
    std::cout << "Input file name is: " << this->inputfile << std::endl;
}

void Winnable::printGameConfiguration() {
    printTheGameConfiguration(&this->game);
}


