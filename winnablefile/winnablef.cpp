//
// Created by wendellbest on 6/9/22.
//
#include "winnable.h"
#include "GameConfiguration.h"
#include <cstdlib>

char movesArr[] = {'.', 'r', '1', '2', '3', '4', '5', '6', '7', 'w', 'f'};

winnable::winnable(bool limitmoves, int numberOfMoves, bool hashtable, bool safeMoves, bool verboseMode){
    this->limitmoves = limitmoves;
    this->numberOfMoves = numberOfMoves;
    this->hashtanle = hashtable;
    this->safeMoves = safeMoves;
    this->verboseMode = verboseMode;

}
/* Case 1: the move is a '.', need to only add that as a source move and nothing
 * in the destination, so set destination to zero.
 * Case 2: the move is a 'r', handle like case 1.
 * Case 3: the move from source to destination is invalid. Need to skip that source.
 * Case 4: the destination is invalid, need to skip it as well.
 * Case 5: valid move, check to see if it is a valid game move, add to list of moves
 * Case 6: valid move, invalid game move, don't add to list
 * Case 7: valid moves, but no valid game moves found
 * Also need to have the function display the number of configurations checked*/
GameConfiguration &winnable::findWinningMoves(GameConfiguration &game) {
    GameConfiguration *tempGame = new GameConfiguration(game);
    //First check to see if the game is in a winnable configuration, if so, return it
    if(tempGame->isGameWinnable()){
        tempGame->setWinningGameConfiguration(true);
        return *tempGame;
    }
    if(tempGame->numberOfMoves() > numberOfMoves){
        tempGame->setWinningGameConfiguration(false);
    }
    // i represents the source, j the destination
    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 11; j++){
            //case 1 and 2
            if(movesArr[i] == '.' || movesArr[i] == 'r'){
                Moves temp(movesArr[i], 0);
                if(advanceConfirmsMoves(*tempGame,temp)){
                    tempGame->addMove(temp);
                    tempGame->gameConfigurationId();
                    findWinningMoves(*tempGame);
                }
                else{
                    break;
                }
            }
            else {
                Moves temp(movesArr[i], movesArr[j]);
                if(temp.isMoveValid()){
                    if(advanceConfirmsMoves(*tempGame,temp)){
                        tempGame->addMove(temp);
                        tempGame->gameConfigurationId();
                        findWinningMoves(*tempGame);
                    }
                }
                else{
                    if(movesArr[i] == 'f')
                        break;
                    else if(movesArr[j] == 'w')
                        continue;
                }
            }
        }
    }
    return game;
}

bool winnable::advanceConfirmsMoves(GameConfiguration &game, Moves move) {
    bool result = false;
    std::string advance = "./cmake-build-debug/advance ";
    std::string exchange = "-x ";
    std::string outputFileSwitch = "-o ";
    std::string outputFileName = writeGameToFileAddMove(game,move);
    std::string argument = advance + exchange + outputFileSwitch + outputFileName + " " + outputFileName;
    if(system(argument.c_str()) == 0)
        result = true;
    return result;
}

std::string winnable::writeGameToFileAddMove(GameConfiguration game, Moves move) {
    std::string outString= "out";
    std::string stringID = std::to_string(game.getGameConfigurationID());
    std::string type = ".txt";
    std::string uniqueOut = outString + stringID + type;
    std::ofstream out(uniqueOut);
    std::cout.rdbuf(out.rdbuf());
    std::cout << "RULES:" << std::endl;
    std::cout << "turn " << game.getRulesTurn() << std::endl;
    if(game.getRulesLimit() == -1)
        std::cout << "unlimited" << std::endl;
    else
        std::cout << "limit " << game.getRulesLimit() << std::endl;
    std::cout << "FOUNDATIONS:" <<std::endl;
    game.printGameFoundation();
    std::cout << "TABLEAU:" << std::endl;
    game.printGameTableau();
    std::cout << "STOCK:" << std::endl;
    game.printGameStock();
    std::cout << "MOVES:" << std::endl;
    move.printMove();
    return uniqueOut;
}

