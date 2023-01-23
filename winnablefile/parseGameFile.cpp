//
// Created by wendellbest on 1/15/23.
//

#include <iostream>
#include <fstream>
#include "parseGameFile.h"

parseGameFile::parseGameFile() {
    inputfile = "";
    game = gameConfiguration();
}

parseGameFile::parseGameFile(std::string inputfile, gameConfiguration game) {
    this->inputfile = inputfile;
    this->game = game;
}

gameConfiguration parseGameFile::getGameFromfile() {
    std::ifstream inputGame{inputfile, std::ios_base::in};
    std::string buffer = "";

    while (getline(inputGame, buffer)) {
        if(buffer[0] == '#')
            continue;
        //Building Rules, if the rules come after the RULES:
        if (buffer.find("RULES:") != std::string::npos) {
            if (buffer.find("turn 1") != std::string::npos) {
                game.setRuleCardTurn(false);
            } else if (buffer.find("turn 3") != std::string::npos) {
                game.setRuleCardTurn(true);
            }
            else
                continue;
            if (buffer.find("unlimited") != std::string::npos) {
                game.setRuleResetLimit(false);
                continue;
            }
            else if (buffer.find("limit") != std::string::npos) {
                int ptr = buffer.find("limit");
                int number = 0;
                while (!std::isdigit(buffer[ptr++]));
                while (std::isdigit(buffer[ptr++])) {
                    number = number * 10;
                    number = number + int(buffer[ptr]) - 48;
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
        if (buffer.find("unlimited") != std::string::npos) {
            game.setRuleResetLimit(false);
        } else if (buffer.find("limit") != std::string::npos) {
            int ptr = buffer.rfind(" ") + 1;
            int number = 0;
            while (std::isdigit(buffer[ptr])) {
                number = number * 10;
                number = number + (buffer[ptr] - '0');
                ptr++;
            }
            game.setRuleResetNumber(number);
        }
        //Building the foundations if they are after FOUNDATIONS:
        if (buffer.find("FOUNDATIONS:") != std::string::npos) {
            int index = buffer.rfind(":") + 1;
            while (!iscntrl(buffer[index])) {
                if (Card::isCardRank(buffer[index]) && Card::isCardSuit(buffer[index + 1])) {
                    Card temp(buffer[index], buffer[index + 1], false);
                    game.addCardToFoundation(temp);
                    index += 2;
                }
                index++;
            }
            //need to build foundation if it is not after Foundations
            //Look for Tableau
            while (getline(inputGame, buffer)) {
                if (buffer.find("TABLEAU:") != std::string::npos)
                    break;
                while (!std::iscntrl(buffer[index])) {
                    if (Card::isCardRank(buffer[index]) && Card::isCardSuit(buffer[index + 1])) {
                        Card temp(buffer[index], buffer[index + 1], false);
                        game.addCardToFoundation(temp);
                        index += 2;
                    }
                    index++;
                }
            }
        }
        //Find the tableau
        if (buffer.find("TABLEAU:") != std::string::npos){
            int col = 7;
            bool isCovered = true;
            //The first time in loop, gets the next line
            while(getline(inputGame,buffer)){
                //If Moves: is found then this is the end of the tableau
                if(buffer.find("STOCK")!= std::string::npos)
                    break;
                //Go through each line after Tableau:
                for(int i = 0; i < buffer.length(); i++){
                    if(Card::isCardRank(buffer[i]) && Card::isCardSuit(buffer[i+1])){
                        Card temp(buffer[i],buffer[i+1], isCovered);
                        game.addCardToTableau(col,temp);
                        i+=2;
                    }
                    else if(buffer[i] == '|'){
                        isCovered = false;
                        Card temp(buffer[i],'n',isCovered);
                        game.addCardToTableau(col,temp);
                        i+=1;
                    }
                }
                //Exiting the inner loop and setting up for the next one
                col-=1;
                isCovered = true;
            }
        }
        //Get the stock if any, stock can be after Stock: or below
        if(buffer.find("STOCK:") != std::string::npos){
            int index = buffer.rfind(":");
            bool covered = false;
            do{
                if(buffer.find("MOVES:")!=std::string::npos)
                    break;
                for(;index < buffer.length(); index++){
                   if(Card::isCardRank(buffer[index]) && Card::isCardSuit(buffer[index+1])){
                       Card temp(buffer[index],buffer[index+1], covered);
                       game.addCardToStockWaste(temp);
                       index+=2;
                   }
                   else if(buffer[index] == '|'){
                       covered = true;
                       Card temp(buffer[index],'n',covered);
                       game.addCardToStockWaste(temp);
                       index+=1;
                   }
                }
                index = 0;
            }while(getline(inputGame,buffer));
        }
        //Get the moves, can be after Moves: or below
        if(buffer.find("MOVES:") != std::string::npos){
            do{
                for(int i = 0; i < buffer.length(); i++){
                    if(Move::isMove(buffer[i],buffer[i+3])){
                        game.addMoveToMoves(Move(buffer[i], buffer[i+3]));
                        i+=4;
                    }
                    else if(Move::isStockMove(buffer[i])){
                        game.addMoveToMoves(Move(buffer[i], 'n'));
                        i+=1;
                    }
                }
            }while(getline(inputGame,buffer));
        }
    }
    return game;
}
