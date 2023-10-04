//
// Created by wendellbest on 3/18/23.
//
#include <iostream>
#include <string>
#include <fstream>
#include "parseFile.h"
#include "gameConfiguration.h"

ParseFile::ParseFile(GameConfiguration game) {
    this->ngame = game;
}

ParseFile::ParseFile(SearchSettings set, GameConfiguration *game) {
    settings = set;
    this->game = game;
}

bool ParseFile::readGameFile() {
    std::ifstream inputFile(settings.getFilename());
    std::string buffer;
    if(!inputFile.is_open())
        return false;
    while (std::getline(inputFile, buffer)) {
        if (buffer.find("RULES:") != std::string::npos) {
            if (buffer.find("turn 3") != std::string::npos) {
                game->setRuleCardTurnover(true);
            }
            if ((buffer.find("limit ") != std::string::npos)) {
                game->setRuleLimitedWasteResets(true);
                int index = buffer.find_last_of("limit");
                std::string numVar = buffer.substr(index);
                std::string numVar1;
                for (int i = 0; i < numVar.length(); i++) {
                    if (std::isdigit(numVar[i]))
                        numVar1.push_back(numVar[i]);
                }
                game->setRuleNumberofWasteResets(std::stoi(numVar1));
            }
        }

        if (buffer.find("turn 3") != std::string::npos) {
            game->setRuleCardTurnover(true);
        }

        if (buffer.find("limit ") != std::string::npos) {
            game->setRuleLimitedWasteResets(true);
            int index = buffer.find_last_of("limit");
            std::string numVar = buffer.substr(index);
            std::string numVar1;
            for (int i = 0; i < numVar.length(); i++) {
                if (std::isdigit(numVar[i]))
                    numVar1.push_back(numVar[i]);
            }
            game->setRuleNumberofWasteResets(std::stoi(numVar1));
        }

        if (buffer.find("FOUNDATIONS:") != std::string::npos) {
            int index = buffer.find_last_of("FOUNDATIONS:");
            int index1 = 0;
            while (buffer.find("TABLEAU:") == std::string::npos) {
                for (int i = index; i < buffer.length(); i++) {
                    if (ranks.find(buffer[i]) != std::string::npos && suits.find(buffer[i + 1]) != std::string::npos) {
                        Card temp(buffer[i], buffer[i + 1], false);
                        game->addCardToFoundations(index1++, temp);
                    }
                    if (index1 == 4)
                        break;

                }
                std::getline(inputFile, buffer);
                index = 0;
            }
        }
        if (buffer.find("TABLEAU:") != std::string::npos) {
            int col = 7;
            bool isCovered = true;
            std::getline(inputFile,buffer);
            while(buffer.find("STOCK:")==std::string::npos){
                for(int i = 0; i < 27; i++){
                    if(iscntrl(buffer[i]))
                        break;
                    if(ranks.find(buffer[i])!=std::string::npos && suits.find(buffer[i+1])!= std::string::npos){
                        Card temp(buffer[i], buffer[i+1], isCovered);
                        game->addCardToTableau(col,temp);
                    }
                    else if(buffer[i] == '|'){
                        Card temp(buffer[i],'0', isCovered);
                        isCovered = false;
                        game->addCardToTableau(col, temp);
                    }
                }
                col--;
                isCovered = true;
                std::getline(inputFile, buffer);
            }
        }
        if (buffer.find("STOCK:") != std::string::npos) {
            bool isCovered = false;
            int index = buffer.find_last_of("STOCK:");
            while(buffer.find("MOVES:")==std::string::npos){
                for(int i = index; i < buffer.length(); i++){
                    if(iscntrl(buffer[i]))
                        break;
                    if(buffer[i] == '|'){
                        Card temp('|', '0', isCovered);
                        isCovered = true;
                        game->addCardToStockWaste(temp);
                    }
                    if(ranks.find(buffer[i])!=std::string::npos && suits.find(buffer[i+1]!= std::string::npos)){
                        Card temp(buffer[i], buffer[i+1], isCovered);
                        game->addCardToStockWaste(temp);
                    }
                }
                std::getline(inputFile, buffer);
                index = 0;
            }
        }
        if (buffer.find("MOVES:") != std::string::npos) {
            //std::cout << "Found Moves" << std::endl;
        }
    }
    inputFile.close();
    return true;
}




