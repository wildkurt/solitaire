//
// Created by wendellbest on 1/22/23.
//

#include <iostream>
#include <fstream>
#include "findWinning.h"
/**This program will need to:
 * 1. Create a output file in the exchange format appended with a list of moves
 * 2. Invoke advance with the correct flags to see if move is valid
 *      a. The flag "-m N" needs to be updated if there is a limit on moves and sent to advance
 *      b. The flag "-o fileOuput" needs to be part of invocation
 *      c: The flag "-x" for exchange format is required to get the file back
 *      d. This is the same as the winnable switch
 * 3. Read the output file from advance into a new game configuration
 *      a. The output file from Advance will not have any moves. In this case, it
 *      would be possible to just append one move at a time to the input file for advance.
 *      Without the need to append all the moves, then the moves in the list of moves will
 *      only be the valid ones.
 * 4. Need to make sure to impliment the "-c" flag for a hash table
 * 5. "-f" for force moves to the foundation
 * 6. "-v" verbose mode, which is just sending notifications to the screen of numbers of
 * configurations checked*/



findWinning::findWinning(SearchSettings settings, gameConfiguration &game): settings(settings), initialGame(game) {}

findWinning::findWinning(const findWinning &wgame){
    settings = SearchSettings (wgame.settings);
    initialGame = wgame.initialGame;
}
findWinning &findWinning::operator=(const findWinning &findb) {
    settings = findb.settings;
    initialGame = findb.initialGame;
    configCount = findb.configCount;
    return *this;
}

bool findWinning::winningGameSearch(gameConfiguration game) {
    bool result = false;
    //Couldn't find a move that is a win
    if(settings.getnMoves() <= game.getMovesSoFar())
        result = false;
    //Check for winning condition
    if(game.accStockInWinning() && game.accTableauInWinning()){
        initialGame = game;
        result = true;
    }
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(from[i] != to[i]){
                if(writeToAdvance(from[i], to[j], game)){
                    gameConfiguration temp;
                    temp = game;
                    temp.addMoveToMoves(Move(from[i], to[j]));
                    temp.setGameId();
                    temp.incrementMovesSoFar();
                    winningGameSearch(temp);
                }
            }
        }
    }
    return result;
}

bool findWinning::writeToAdvance(char rom, char tO, gameConfiguration configuration) {
    std::string adInputFileName = "input";
    std::string inputTXT = configuration.getGameId();
    adInputFileName.append(inputTXT);
    adInputFileName.append(".txt");
    std::ofstream inputFile(adInputFileName,std::ios_base::out);

    inputFile << "RULES:" << std::endl;
    Rules tempr = configuration.getRules();
    if(tempr.getTurn3Cards())
        inputFile << "turn 3" << std::endl;
    else
        inputFile << "turn 1" << std::endl;
    if(tempr.getResetsLimited())
        inputFile << "limit" << tempr.getResetLimit() << std::endl;
    else
        inputFile << "unlimited" << std::endl;
    inputFile << "FOUNDATION:" << std::endl;
    Foundation tempf = configuration.getFoundation();
    for(int i =0; i < 4; i++)
        inputFile << tempf.getCard(i).getRank() << tempf.getCard(i).getCardSuit() << " ";
    inputFile << std::endl;
    inputFile << "TABLEAU:" << std::endl;
    return false;
}

