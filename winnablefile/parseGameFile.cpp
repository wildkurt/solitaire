//
// Created by wendellbest on 1/15/23.
//

#include <iostream>
#include <fstream>
#include <string>
#include "parseGameFile.h"

parseGameFile::parseGameFile() {
    inputfile=nullptr;
    game = gameConfiguration();
}

parseGameFile::parseGameFile(std::string inputfile, gameConfiguration game) {
    this->inputfile = inputfile;
    this->game = game;
}

gameConfiguration parseGameFile::getGameFromfile() {
    std::ifstream inputGame{inputfile, std::ios_base::in};
    std::string buffer = 0;

    while (getline(inputGame, buffer)) {
        //Building Rules, if the rules come after the RULES:
        if (buffer.find("RULES:") != std::string::npos) {
            if (buffer.find("turn 1") != std::string::npos) {
                game.setRuleCardTurn(false);
            } else if (buffer.find("turn 3") != std::string::npos) {
                game.setRuleCardTurn(true);
            }
            if (buffer.find("unlimited") != 0) {
                game.setRuleResetLimit(false);
            } else if (buffer.find("limit") != 0) {
                int ptr = buffer.find("limit");
                int number = 0;
                while (!std::isdigit(buffer[ptr++]));
                while (std::isdigit(buffer[ptr++])) {
                    number = number * 10;
                    number = number + (buffer[ptr] - '0');
                }
                game.setRuleResetNumber(number);
            }
        }
        //Building rules if they are below RULES:
        if (buffer.find("turn 1") != std::string::npos) {
            game.setRuleCardTurn(false);
        } else if (buffer.find("turn 3") != std::string::npos) {
            game.setRuleCardTurn(true);
        }
        if (buffer.find("unlimited") != 0) {
            game.setRuleResetLimit(false);
        } else if (buffer.find("limit") != 0) {
            int ptr = buffer.find("limit");
            int number = 0;
            while (!std::isdigit(buffer[ptr++]));
            while (std::isdigit(buffer[ptr++])) {
                number = number * 10;
                number = number + (buffer[ptr] - '0');
            }
            game.setRuleResetNumber(number);
        }
        //Building the foundations if they are after FOUNDATIONS:
        if (buffer.find("FOUNDATIONS:") != std::string::npos) {
            int index = buffer.rfind("FOUNDATIONS:") + 1;
            while (buffer[index] != '\n') {
                if (Card::isCardRank(buffer[index]) && Card::isCardSuit(buffer[index + 1])) {
                    Card temp(buffer[index], buffer[index + 1], false);
                    game.addCardToFoundation(temp);
                    index += 2;
                }
            }
            //need to build foundation if it is not after Foundations
            //Look for Tableau
            while (getline(inputGame, buffer)) {}
            if (buffer.find("TABLEAU:") != std::string::npos)
                break;
            while (buffer[index] != '\n') {
                if (Card::isCardRank(buffer[index]) && Card::isCardSuit(buffer[index + 1])) {
                    Card temp(buffer[index], buffer[index + 1], false);
                    game.addCardToFoundation(temp);
                    index += 2;
                }
            }
        }
        if (buffer.find("TABLEAU:") != std::string::npos){
            int col = 7;
            bool isCovered = true;
            //The first time in loop, gets the next line
            while(getline(inputGame,buffer)){
                //If Moves: is found then this is the end of the tableau
                if(buffer.find("STOCK")!= std::string::npos)
                    break;
                //Go through each line after Tableau:
                for(int i = 0; buffer[i] != '\n'; i++){
                    if(Card::isCardRank(buffer[i]) && Card::isCardSuit(buffer[i+1])){
                        Card temp(buffer[i],buffer[i+1], isCovered);
                        game.addCardToTableau(col,temp);
                    }
                    else if(buffer[i] == '|'){
                        isCovered = false;
                        Card temp(buffer[i],'n',isCovered);
                        game.addCardToTableau(col,temp);
                    }
                }
                //Exiting the inner loop and setting up for the next one
                col-=1;
                isCovered = true;
            }
        }
        //Get the stock if any, stock can be after Stock: or below
        if(buffer.find("STOCK:") != std::string::npos){
            int index = buffer.rfind("STOCK:");
            bool covered = false;
            do{
                if(buffer.find("MOVES:")!=std::string::npos)
                    break;
                for(;buffer[index] != '\n'; index++){
                   if(Move::isMove(buffer[index],buffer[index+3])){
                       Card temp(buffer[index],buffer[index+3], covered);
                       game.addCardToStockWaste(temp);
                   }
                   else if(buffer[index] == '|'){
                       covered = true;
                       Card temp(buffer[index],'n',covered);
                       game.addCardToStockWaste(temp);
                   }
                }
            }while(getline(inputGame,buffer));
        }
        //Get the moves, can be after Moves: or below
        if(buffer.find("MOVES:") != std::string::npos){
            do{
                for(int i = 0; buffer[i] != '\n'; i++){
                    if(Move::isMove(buffer[i],buffer[i+3])){
                        game.addMoveToMoves(Move(buffer[i], buffer[i+3]));
                    }
                    else if(Move::isStockMove(buffer[i])){
                        game.addMoveToMoves(Move(buffer[i], 'n'));
                    }
                }
            }while(getline(inputGame,buffer));
        }
    }
    return game;
}
