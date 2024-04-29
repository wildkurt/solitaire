//
// Created by wendellbest on 3/5/24.
//
#include <iostream>
#include <string>
#include <cstring>
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

void Winnable::retrieveCommandLineArguments(int args, char **argv) {
    for(int i = 1; i < args ; i++){
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

bool Winnable::getGameFile(std::string filename) {
    /*The game file can come from stdin or a file. The command line arguments determine that.*/
    std::fstream writeToFile;
    if(this->inputfile.empty()){
        //Get file from stdin. If the file goes straight to check, then it is gone. Need to make copy of the file
        //for check.
        writeToFile.open(filename, std::fstream::out | std::fstream::trunc);
        if(writeToFile.is_open()){
            for(std::string buffer; std::getline(std::cin, buffer);){
                writeToFile << buffer << std::endl;
            }
        }
        writeToFile.close();
    }
    this->inputfile = filename;
    if(this->checkGameFile(this->inputfile)){
        getTheGameConfigFromFile(&this->game,(char *)this->inputfile.c_str());
    }
    else{
        return false;
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

bool Winnable::checkGameFile(std::string filename) {
    FILE *ptr;
    std::string command = "./check ";
    char buffer[MAX_BUFFER] = {0};

    command.append(filename);
    ptr = popen(command.c_str(), "r");
    if(ptr == nullptr){
        std::cerr << "Unable to open " << filename << std::endl;
        return false;
    }
    while(fgets(buffer, MAX_BUFFER, ptr) != nullptr){
        std::string temp = buffer;
        if(temp.find("Input file is valid") != std::string::npos)
            break;

    }
    if(strlen(buffer) == 0)
        return false;
    return true;
}

bool Winnable::isGameWinnable(Move *pMove, int validMoves, int *numberOfConfigurations) {
    std::string movesFrom = "1234567", movesTo = "1234567", movesFromWasteTo = "1234567f";
    std::string advanceoutput = "advanceoutput.txt", winnableoutput = "winnableoutput.txt";

    //Winnable game configuration
    if(this->gameIsInGauranteedWinCondition())
        return true;

    //Not winnable within a number of moves
    if(this->movestoplay <= validMoves)
        return false;

    //Can any tableau cards be moved to foundations
    for(int i = 6; i < movesFrom.length(); i--){
        this->printGameToFile(winnableoutput);
        this->inputfile = winnableoutput;
        this->appendMoveToFile(movesFrom[i], 'f', 0);
        if(this->isMoveValid(winnableoutput)){
            Move temp = {'f', movesFrom[i],0};
            pMove[validMoves] = temp;
            Winnable newConfig = *this;
            newConfig.getGameFile(advanceoutput);
            if(newConfig.isGameWinnable(pMove, ++validMoves, numberOfConfigurations))
               return true;
        }
    }

    //Can any tableau cards be moved to another column
    for(int i = 6; i >= 0; i--){
        for(int j = 0; j < movesTo.length(); j--){
            this->printGameToFile(winnableoutput);
            this->inputfile = winnableoutput;
            this->appendMoveToFile(movesFrom[i], movesTo[j], 0);
            if(this->isMoveValid(winnableoutput)){
                Move temp = {movesTo[j], movesFrom[i], 0};
                pMove[validMoves] = temp;
                Winnable newConfig = *this;
                newConfig.getGameFile(advanceoutput);
                if(newConfig.isGameWinnable(pMove, ++validMoves, numberOfConfigurations))
                    return true;
            }
        }
    }
    //Can any waste card be moved to tableau or foundation
    for(int i = 0; i < movesFromWasteTo.length(); i++){
        this->printGameToFile(winnableoutput);
        this->inputfile = winnableoutput;
        this->appendMoveToFile('w', movesFromWasteTo[i], 0);
        if(this->isMoveValid(winnableoutput)){
            Move temp = {movesFromWasteTo[i], 'w', 0};
            pMove[validMoves] = temp;
            Winnable newConfig = *this;
            newConfig.getGameFile(advanceoutput);
            if(newConfig.isGameWinnable(pMove, ++validMoves, numberOfConfigurations))
                return true;
        }
    }
    //If no moves are valid, turn stock card over, reset stock pile if no more stock cards
    this->printGameToFile(winnableoutput);
    this->inputfile = winnableoutput;
    this->appendMoveToFile(0,0,'.');
    if(this->isMoveValid(winnableoutput)){
        Move temp = {0,0, '.'};
        pMove[validMoves] = temp;
        Winnable newConfig = *this;
        newConfig.getGameFile(advanceoutput);
        if(newConfig.isGameWinnable(pMove, validMoves, numberOfConfigurations))
            return true;
    }

    this->printGameToFile(winnableoutput);
    this->inputfile = winnableoutput;
    this->appendMoveToFile(0,0,'r');
    if(this->isMoveValid(winnableoutput)){
        Move temp = {0,0, 'r'};
        pMove[validMoves] = temp;
        Winnable newConfig = *this;
        newConfig.getGameFile(advanceoutput);
        if(newConfig.isGameWinnable(pMove, validMoves, numberOfConfigurations))
            return true;
    }

    return false;
}

void Winnable::printGameToFile(std::string filenameString) {

    const char *filename = filenameString.c_str();

    FILE *fileptr = fopen(filename, "w");

    printRulesToFile(fileptr, &this->game.rules);
    printFoundationToFile(fileptr, &this->game.foundation);
    printTableauToFile(fileptr,&this->game.tableau);
    printStockWasteToFile(fileptr,&this->game.stockwaste);
    fputs("MOVES:\n", fileptr);

    fclose(fileptr);
}

void Winnable::appendMoveToFile(char i, char j, char k) {
    std::fstream appendmove;
    appendmove.open(this->inputfile, std::fstream::out | std::fstream::app);
    if(!appendmove.is_open()){
        std::cerr << "Unable to open " << this->inputfile << " for appending move." << std::endl;
        exit(1);
    }
    if(i !=0 && j != 0 && k == 0)
        appendmove << i << "->" << j << std::endl;
    else
        appendmove << k << std::endl;
    appendmove.close();
}

bool Winnable::isMoveValid(std::string outputfilename) {
    FILE *ptr;
    char buffer[MAX_BUFFER] = {0};

    std::string command = "./advance ";
    command.append(this->inputfile);
    command.append(" -o ");
    command.append(outputfilename);

    ptr = popen((const char*) command.c_str(), "r");

    while(fgets(buffer,MAX_BUFFER,ptr) != nullptr){
        std::string stringBuffer = buffer;
        if(stringBuffer.find("Processed ") && stringBuffer.find(" moves, all valid"))
            return true;
    }
    return false;
}

bool Winnable::gameIsInGauranteedWinCondition() {
    int coveredCards = 0, stockCards = 0, wasteCards = 0;

    for(int i = 1; i < 8; i++){
        Card *ptr = getPointerToColumn(i, &this->game.tableau);
        for(int j = 0; ptr[j].rank != 0; j++){
            if(ptr[j].faceUp == 'f'){
                coveredCards++;
            }
        }
    }
    Card *swptr = (Card *) &this->game.stockwaste.sw;
    for(int i = 0; swptr[i].rank != 0; i++){
        if(swptr[i].faceUp == 't')
            wasteCards++;
        else if(swptr[i].faceUp == 'f')
            stockCards++;
    }
    if(coveredCards == 0 && stockCards == 0 && wasteCards <= 1)
        return true;

    return false;
}











