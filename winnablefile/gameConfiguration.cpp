//
// Created by wendellbest on 5/19/22.
//

#include "gameConfiguration.h"
#include <iostream>
#include <fstream>
#include "cardHeader.h"

GameConfiguration::GameConfiguration(Switches p) {
    GameConfiguration::parseInputFile(p);
}
//Reads the input file and stores the card values, not required to read from
//standard input
int GameConfiguration::parseInputFile(Switches input){
    unsigned long positionof = 0, positinaft = 0;
    char const *digits = "0123456789";
    bool foundFoundations = false;
    std::string line;
    std::ifstream inputFile(input.getInputFileName(),std::ios::in);

    if(!inputFile) {
        std::cerr << "File " << input.getInputFileName() << " not found" << std::endl;
    }
    else{
        //Maybe nested loops to control flow?
        while(getline(inputFile, line)){
            if(line.find("RULES:") != std::string::npos){
                /**Case 1: the rules for turn and unlimited come after RULES:
                 * Case 2: the rules are below RULES: and in line
                 * Case 3: the rules are on seperate lines*/
                 //Look on same line as Rules
                if(line.find("turn 3") != std::string::npos){
                    std::cout << "Found \"turn\""<<std::endl;
                    rules.setTurn('y');
                }
                if((positionof = line.find("limit ") )!= std::string::npos){
                    positionof = line.find_first_of(digits, positionof);
                    positinaft = line.find_first_not_of(digits, positionof);
                    std::string numberS = line.substr(positionof, positinaft);
                    rules.setResetNumber(stoi(numberS));
                    std::cout << "Reset is "<< rules.getResetNumber()<<std::endl;
                }
            }
            //the next two if statements will handle case 2 and 3
            if(line.find("turn 3") != std::string::npos){
                rules.setTurn(true);
            }
            if((positionof = line.find("limit ") )!= std::string::npos){
                positionof = line.find_first_of(digits, positionof);
                positinaft = line.find_first_not_of(digits, positionof);
                std::string numberS = line.substr(positionof, positinaft);
                rules.setLimit(true);
                rules.setResetNumber(stoi(numberS));
                std::cout << "Reset is "<< rules.getResetNumber()<<std::endl;
            }
            /**Case 1: the foundation cards are on the same line as FOUNDATIONS:
             * Case 2: the foundations cards are below FOUNDATIONS: and in line
             * Case 3: the foundations are on seperate lines*/
            if(line.find("FOUNDATIONS:") != std::string::npos){
                //Case 1: the cards follow after foundations
                // Move to spot after foundations then start looking for cards
                foundFoundations = true;
                positinaft = line.find_first_of(":");
                if(positinaft != std::string::npos) {
                    for (int i = positinaft; line[i] != '\0'; i++) {
                        if (isValidRank(line[i]) && isValidSuit(line[i + 1])) {
                            Card temp(line[i], line[i + 1], false);
                            if (!foundation.addCardToFoundation(temp)) {
                                std::cerr << "Card " << temp.getRank() << temp.getSuit() << " Not Added" << std::endl;
                            }
                        }
                    }
                }
                else{ getline(inputFile,line);}
            }
            //Case 2 and 3: The cards are on one line below foundations
            // Move to next line and keep looking for cards
            if(!foundation.isFoundationFull() && foundFoundations) {
                for (int i = 0, j = 0; line[i] != '\0'; i++) {
                    if (isValidRank(line[i]) && isValidSuit(line[i+1])) {
                        Card temp(line[i], line[i + 1], false);
                        if (!foundation.addCardToFoundation(temp)) {
                            std::cerr << "Card " << temp.getRank() << temp.getSuit() << " Not Added" << std::endl;
                        }
                    }
                }
            }
            //The columns for tableau will always be after tableau
            if(line.find("TABLEAU:") != std::string::npos && !tableau.isColumnFilled(7)){
                int column = 7;
                while(getline(inputFile, line)){
                    bool covered = true;
                    for(int i = 0; line[i] != '\0'; i++){
                        if(isValidRank(line[i]) && isValidSuit(line[i+1])){
                            Card temp (line[i], line[i+1], covered);
                            if(!tableau.addCardToTableau(temp, column)){
                                std::cerr << "Unable to add " << line[i] << line[i+1]<<std::endl;
                            }
                        }
                        else if(line[i] == '|'){
                            Card temp (line[i], line[i+1], covered = false);
                            if(!tableau.addCardToTableau(temp, column)){
                                std::cerr << "Unable to add " << line[i] << line[i+1]<<std::endl;
                            }
                        }
                    }
                    tableau.columnFilled(column);
                    column--;
                    if(column == 0)
                        break;
                }
            }
            if(line.find("STOCK:") != std::string::npos){
                bool stockCovered = false;
                std::cout << "Found STOCK"<<std::endl;
                /* Case 1: The cards in stock could start after STOCK:
                 * Case 2: The cards are below STOCK:
                 * Case 3: There are no cards, just the divider
                 * Need to stop before MOVES:, */
                positinaft = line.find_first_of(":");
                if(positinaft != std::string::npos) {
                    for (long int i = positinaft, j = 0; line[i] != '\0'; i++) {
                        if (isValidRank(line[i]) && isValidSuit(line[i + 1])) {
                            Card temp(line[i], line[i + 1], stockCovered);
                            stockwaste.addCard(temp, j++);
                        }
                        else if(line[i] == '|'){
                            stockCovered = true;
                            Card temp(line[i], '_', stockCovered);
                            stockwaste.addCard(temp, j++);
                        }
                    }
                }
                while(line.find("MOVES:") != std::string::npos && getline(inputFile, line)){
                    for (long int i = positinaft, j = 0; line[i] != '\0'; i++) {
                        if (isValidRank(line[i]) && isValidSuit(line[i + 1])) {
                            Card temp(line[i], line[i + 1], false);
                            stockwaste.addCard(temp, j++);
                        }
                    }
                }

            }
            if(line.find("MOVES:") != std::string::npos){
                std::cout << "Found MOVES"<<std::endl;
                positinaft = line.find_first_of(":");
                for(long int i = positinaft; line[i] != '\0'; i++){
                    if(isValidFromMove(line[i]) && isValidToMove(line[i+3])){
                        Moves temp(line[i], line[i+3]);
                        moves.push_back(temp);
                    }
                    else if(isValidAction(line[i])){
                        Moves temp(line[i]);
                    }
                }
            }
        }
    }
    return 1;
}

bool GameConfiguration::isValidRank(char c) {
    switch (c){
        case '_' : return true;
        case '1' : return true;
        case '2' : return true;
        case '3' : return true;
        case '4' : return true;
        case '5' : return true;
        case '6' : return true;
        case '7' : return true;
        case '8' : return true;
        case '9' : return true;
        case 'T' : return true;
        case 'J' : return true;
        case 'Q' : return true;
        case 'K' : return true;
        default : return false;
    }
}
bool GameConfiguration::isValidSuit(char c){
    switch(c){
        case 'd' : return true;
        case 'h' : return true;
        case 'c' : return true;
        case 's' : return true;
        default: return false;
    }
}
void GameConfiguration::printCardArrays() {
    std::cout << "Foundations" << std::endl;
    for(int i = 0; i < 4; i++){
        std::cout << foundation.getFoundation(i).getRank() << foundation.getFoundation(i).getSuit() << " ";
    }
    std::cout << std::endl;
    for(int i = 7; i > 0; i--){
        long size = tableau.getTableauColSize(i);
        for(int j = 0; j < size; j++){
            if(j == 0)
                std::cout << "Tableau " << i <<": ";
            Card temp = tableau.getCard(j,i);
            std::cout << temp.getRank() << temp.getSuit() << " ";
        }
        std::cout << std::endl;
    }
}

bool GameConfiguration::isValidFromMove(char c) {
    bool result = false;
    switch(c){
        case 'w' : result = true; break;
        case '1' : result = true; break;
        case '2' : result = true; break;
        case '3' : result = true; break;
        case '4' : result = true; break;
        case '5' : result = true; break;
        case '6' : result = true; break;
        case '7' : result = true; break;
    }
    return result;
}

bool GameConfiguration::isValidToMove(char c) {
    bool result = false;
    switch(c){
        case 'f' : result = true; break;
        case '1' : result = true; break;
        case '2' : result = true; break;
        case '3' : result = true; break;
        case '4' : result = true; break;
        case '5' : result = true; break;
        case '6' : result = true; break;
        case '7' : result = true; break;
    }
    return result;
}

bool GameConfiguration::isValidAction(char c) {
    bool result = false;
    switch(c){
        case '.' : result = true; break;
        case 'r' : result = true; break;
        case '|' : result = true; break;
    }
    return result;
}
