//
// Created by wendellbest on 5/19/22.
//

#ifndef SOLITAIRE_SWITCHES_H
#define SOLITAIRE_SWITCHES_H

#include <string>

class Switches{
private:
    char limitedMoves;
    char hashTable;
    char safeMoves;
    char verboseMode;
    int numberOfMoves;
    std::string inputFile;
public:
    Switches(){
        limitedMoves = 'n';
        hashTable = 'n';
        safeMoves = 'n';
        verboseMode = 'n';
        numberOfMoves = 1000;
        inputFile = "";
    }

    Switches(char limMove, char hash, char safe, char verb, int number, std::string file){
        limitedMoves = limMove;
        hashTable = hash;
        safeMoves = safe;
        verboseMode = verb;
        numberOfMoves = number;
        inputFile = file;
    }

    Switches(const Switches &old){
        this->limitedMoves = old.limitedMoves;
        this->hashTable = old.hashTable;
        this->safeMoves = old.safeMoves;
        this->verboseMode = old.verboseMode;
        this->numberOfMoves = old.numberOfMoves;
        this->inputFile = old.inputFile;
    }

    void setLimitedMoves(char c){limitedMoves = c;}
    char getLimitedMoves(){return limitedMoves;}
    void setHashTable(char c){hashTable = c;}
    char getHashTable(){return hashTable;}
    void setSafeMoves(char c){safeMoves = c;}
    char getSafeMoves(){return safeMoves;}
    void setVerboseMode(char c){verboseMode = c;}
    char getVerboseMode(){return verboseMode;}
    void setNumberOfMoves(int n){numberOfMoves = n;}
    int getNumberOfMoves(){return numberOfMoves;}
    void setInputFileName(std::string file){inputFile = file;}
    std::string getInputFileName(){return inputFile;}
};


#endif //SOLITAIRE_SWITCHES_H
