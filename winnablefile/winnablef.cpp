//
// Created by wendellbest on 6/9/22.
//
#include "winnable.h"
#include "GameConfiguration.h"

char movesArr[] = {'.', 'r', '1', '2', '3', '4', '5', '6', '7', 'w', 'f'};

winnable::winnable(bool limitmoves, int numberOfMoves, bool hashtable, bool safeMoves, bool verboseMode){
    this->limitmoves = limitmoves;
    this->numberOfMoves = numberOfMoves;
    this->hashtanle = hashtable;
    this->safeMoves = safeMoves;
    this->verboseMode = verboseMode;

}

GameConfiguration &winnable::findWinningMoves(GameConfiguration &game) {
    if(game.isGameWinnable()){
        game.setWinningGameConfiguration(true);
        return game;
    }
    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 11; j++){
            Moves temp(movesArr[i],movesArr[j]);
        }
    }
    return game;
}
