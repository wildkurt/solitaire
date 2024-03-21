//
// Created by wendellbest on 3/5/24.
//
#include <iostream>
#include <string>
#include <cstring>
#include <array>
#include <memory>
#include <fstream>
#include "winnable.h"
#include "../commonfiles/tableau.h"

Winnable::Winnable() {
    limitmoves = false;
    movestoplay = 1000;
    useHashTable = false;
    foundationSafeMoves = false;
    verboseMode = false;
    inputfile = "";
    outputfile = "exchange2.txt";
    game = {.rules = {.wasteResets = 0, .cardTurnover = 0}, .foundation = {.foundation = {0}}, .tableau ={.tab1 = {0},
          .tab2 = {0}, .tab3 = {0}, .tab4 = {0}, .tab5 = {0}, .tab6 = {0}, .tab7 = {0}}, .stockwaste = {.sw = {0}}};
}

Winnable::Winnable(const Winnable &w) {
    this->limitmoves = w.limitmoves;
    this->movestoplay = w.movestoplay;
    this->useHashTable = w.useHashTable;
    this->foundationSafeMoves = w.foundationSafeMoves;
    this->verboseMode = w.verboseMode;
    this->inputfile = w.inputfile;
    this->outputfile = w.outputfile;
    this->game.rules = w.game.rules;
    for(int i = 0; w.game.foundation.foundation[i].rank != 0; i++){
        this->game.foundation.foundation[i] = w.game.foundation.foundation[i];
    }
    for(int i = 0; i < 22; i++){
        this->game.tableau.tab1[i] = w.game.tableau.tab1[i];
        this->game.tableau.tab2[i] = w.game.tableau.tab2[i];
        this->game.tableau.tab3[i] = w.game.tableau.tab3[i];
        this->game.tableau.tab4[i] = w.game.tableau.tab4[i];
        this->game.tableau.tab5[i] = w.game.tableau.tab5[i];
        this->game.tableau.tab6[i] = w.game.tableau.tab6[i];
        this->game.tableau.tab7[i] = w.game.tableau.tab7[i];
    }
    for(int i = 0; i < 26; i++){
        this->game.stockwaste.sw[i] = w.game.stockwaste.sw[i];
    }
}
Winnable &Winnable::operator=(const Winnable &w) {
    this->limitmoves = w.limitmoves;
    this->movestoplay = w.movestoplay;
    this->useHashTable = w.useHashTable;
    this->foundationSafeMoves = w.foundationSafeMoves;
    this->verboseMode = w.verboseMode;
    this->inputfile = w.inputfile;
    this->outputfile = w.outputfile;
    this->game.rules = w.game.rules;
    for(int i = 0; w.game.foundation.foundation[i].rank != 0; i++){
        this->game.foundation.foundation[i] = w.game.foundation.foundation[i];
    }
    for(int i = 0; i < 22; i++){
        this->game.tableau.tab1[i] = w.game.tableau.tab1[i];
        this->game.tableau.tab2[i] = w.game.tableau.tab2[i];
        this->game.tableau.tab3[i] = w.game.tableau.tab3[i];
        this->game.tableau.tab4[i] = w.game.tableau.tab4[i];
        this->game.tableau.tab5[i] = w.game.tableau.tab5[i];
        this->game.tableau.tab6[i] = w.game.tableau.tab6[i];
        this->game.tableau.tab7[i] = w.game.tableau.tab7[i];
    }
    for(int i = 0; i < 26; i++){
        this->game.stockwaste.sw[i] = w.game.stockwaste.sw[i];
    }
    return *this;
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
    std::string command = "./advance -x ", result, outputFromAdvance = "exchange2.txt";
    FILE *advancePTR, *getGF;
    int index = 0;

    if(this->inputfile.empty()){
        //Run Advance without a file name
        command.append(" -o ");
        command.append(this->inputfile);
        std::cout << command << std::endl;
        advancePTR = popen(command.c_str(), "r");
    }
    else{
        //Run advance with a file name
        command.append(this->inputfile);
        command.append(" -o ");
        command.append(this->outputfile);
        std::cout << command << std::endl;
        advancePTR = popen(command.c_str(), "r");
    }
    if(advancePTR == NULL){
        std::cerr << "File " << this->inputfile << " not found." << std::endl;
        return false;
    }
    while(fgets(buffer, MAX_BUFFER, advancePTR)!=NULL){
        result = buffer;

        if(result.find("moves, all valid") != std::string::npos){
            char *filename = (char *)outputFromAdvance.c_str();
            getTheGameConfigFromFile(&this->game, filename);
        }
        else{
            std::cout << result << std::endl;
        }
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

bool Winnable::checkForWinningCondition(std::string command) {
    std::array <char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    int covered = -1, stock = -1, waste = -1;

    if(!pipe) throw std::runtime_error("popen() failed!");
    while(!feof(pipe.get())){
        if(fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result = buffer.data();
        if(result.find("covered cards") != std::string::npos){
            covered = getNumberFromString(result);
        }
        if(result.find("stock cards") != std::string::npos){
            stock = getNumberFromString(result);
        }
        if(result.find("waste cards") != std::string::npos){
            waste = getNumberFromString(result);
        }
    }
    if(covered == 0 && stock == 0 && waste <= 1)
        return true;
    return false;
}

int Winnable::getNumberFromString(std::string result) {
    const char *digits = "0123456789";
    int resultNumber = -1;
    std::size_t const n = result.find_first_of(digits);
    if (n != std::string::npos)
    {
        std::size_t const m = result.find_first_not_of(digits, n);
        resultNumber = stoi( result.substr(n, m != std::string::npos ? m-n : m));
    }
    return resultNumber;
}
// This function is called by winnable.searchForWinningSeriesOfMovies and needs to be recursive in nature.
bool Winnable::searchForWinningSeriesOfMoves(int *movesSoFar, Winnable winnable, Move *winninglist) {
    //Strings of moves to check
    std::string movesFrom = "w1234567.r", movesTo = "1234567f";

    //File stream to append game text file
    std::fstream appendGameFileWithMove;
    //Get a local copy of the winnable object
    if(winnable.checkForWinningCondition("./check " + winnable.inputfile))
        return true;
    if(winnable.movestoplay == *movesSoFar)
        return false;
    Winnable current(winnable);
    current.inputfile = "exchange1.txt";

    for(int i = 0; i < movesFrom.length(); i++){
        for(int j = 0; j < movesTo.length(); j++){
            current.printGameToExchangeFile();
            appendGameFileWithMove.open(current.inputfile, std::fstream::out | std::fstream::app);
            if(movesFrom[i] == '.' || movesFrom[i] == 'r'){
                appendGameFileWithMove << movesFrom[i] << std::endl;
                appendGameFileWithMove.close();
                if(current.checkForValidMove()){
                    Move temp = {0, 0, movesFrom[i]};
                    winninglist[*movesSoFar] = temp;
                    (*movesSoFar)++;
                    return searchForWinningSeriesOfMoves(movesSoFar, current, winninglist);
                }
                break;
            }
            else if(movesFrom[i] == movesTo[j]){
                continue;
            }
            else{
                appendGameFileWithMove << movesFrom[i] << "->" << movesTo[j] << std::endl;
                appendGameFileWithMove.close();
                if(current.checkForValidMove()){
                    Move temp = {movesTo[i], movesFrom[j], 0 };
                    winninglist[*movesSoFar] = temp;
                    (*movesSoFar)++;
                    return searchForWinningSeriesOfMoves(movesSoFar, current, winninglist);
                }
            }
        }
    }
    return false;
}

void Winnable::printListOfWinningMoves(Move *pMove) {
    for(int i = 0; pMove[i].from != 0 || pMove[i].actionn != 0; i++){
        if(pMove[i].actionn != 0)
            std::cout << pMove[i].actionn << std::endl;
        else
            std::cout << pMove[i].from << "->" << pMove[i].to << std::endl;
    }
}

void Winnable::printGameToExchangeFile() {
    FILE *outputFile;
    char *cOutputFileName = (char *)this->inputfile.c_str();
    outputFile = fopen(cOutputFileName, "w");
    printRulesToFile(outputFile, &this->game.rules);
    printFoundationToFile(outputFile, &this->game.foundation);
    printTableauToFile(outputFile,&this->game.tableau);
    printStockWasteToFile(outputFile, &this->game.stockwaste);
    fprintf(outputFile, "MOVES:\n");
    fclose(outputFile);
}

bool Winnable::checkForValidMove() {
    std::array <char, 128> buffer{};
    std::string command = "./advance -x -s ", result;
    command.append(this->inputfile);
    command.append(" -o ");
    command.append(this->outputfile);
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    if(!pipe) throw std::runtime_error("popen() failed!");
    char *readFile = (char *) this->outputfile.c_str();
    while(!feof(pipe.get())){
        if(fgets(buffer.data(), 128, pipe.get()) != nullptr){
            result = buffer.data();
            std::cout << result << std::endl;
        }
        if(result.find("Processed 1 moves, all valid") != std::string::npos){
            getTheGameConfigFromFile(&this->game, readFile);
            return true;
        }
    }
    return false;
}








