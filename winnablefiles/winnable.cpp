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
    std::string command = "./advance -o exchange2.txt -x ", result, inputfromAdvance = "exchange2.txt";
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
    while(fgets(buffer, MAX_BUFFER, advancePTR)!=NULL){
        result = buffer;

        if(result.find("moves, all valid") != std::string::npos){
            char *filename = (char *)inputfromAdvance.c_str();
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
    //The strings of moves
    std::string movesFrom = "w1234567.r";
    std::string movesTo = "1234567f";
    std::fstream writeExchange1File;
    //local copy of the Winnable object
    Winnable current(winnable);
    //Print the game config to a file
    current.inputfile = "exchange1.txt";
    current.printGameToExchangeFile();
    // See if game is in winning configuration
    std::string commandToCheck = "./check ";
    commandToCheck.append(current.inputfile);
    if(this->checkForWinningCondition(commandToCheck)){
        return true;
    }
    //See if we have reached or exceeded the moves limit
    else if(this->movestoplay <= *movesSoFar){
        return false;
    }
    else{
        for(int i = 0; i < movesFrom.length(); i++){
            for(int j = 0; j < movesTo.length(); j++){
                //Input exchange1.txt to advance, retrieve exchange2.txt from advance
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
    std::fstream writeExchangeFile;
    writeExchangeFile.open(this->inputfile, std::fstream::out | std::fstream::trunc);
    writeExchangeFile << "RULES:" << std::endl;
    writeExchangeFile << " turn " << this->game.rules.cardTurnover << std::endl;
    if(this->game.rules.wasteResets > -1)
        writeExchangeFile << " limit " << this->game.rules.wasteResets << std::endl;
    else
        writeExchangeFile << " unlimited " << std::endl;
    writeExchangeFile << "FOUNDATIONS:" << std::endl;
    for(int i = 0; i < 4; i++){
        writeExchangeFile << " " << this->game.foundation.foundation[i].rank << this->game.foundation.foundation[i].suit;
    }
    writeExchangeFile << std::endl;
    writeExchangeFile << "TABLEAU:" << std::endl;
    for(int i = 7; i >0; i--){
        Card *ptr = getPointerToColumn(i, &this->game.tableau);
        writeExchangeFile << " ";
        for(int j = 0; ptr[j].rank != 0; j++){
            if(ptr[j].faceUp == 'f' && ptr[j+1].faceUp == 't')
                writeExchangeFile << ptr[j].rank << ptr[j].suit << " | ";
            else if(ptr[j].faceUp == 't' && ptr[j+1].faceUp == 0)
                writeExchangeFile << " | " << ptr[j].rank << ptr[j].suit;
            else
                writeExchangeFile << ptr[j].rank << ptr[j].suit << " ";
        }
        writeExchangeFile << std::endl;
    }
    writeExchangeFile << "STOCK:" << std::endl;
    for(int i = 0; this->game.stockwaste.sw[i].rank != 0; i++){
        if(this->game.stockwaste.sw[i].faceUp == 't' && (this->game.stockwaste.sw[i+1].faceUp == 'f' || this->game.stockwaste.sw[i+1].faceUp == 0)){
            writeExchangeFile << this->game.stockwaste.sw[i].rank << this->game.stockwaste.sw[i].suit << " | ";
        }
        else{
            writeExchangeFile << this->game.stockwaste.sw[i].rank << this->game.stockwaste.sw[i].suit << " ";
        }
    }
    writeExchangeFile << std::endl;
    writeExchangeFile << "MOVES:" << std::endl;
}








