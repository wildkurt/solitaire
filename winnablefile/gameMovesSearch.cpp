//
// Created by wendellbest on 9/4/22.
//

#include "gameMovesSearch.h"

gameBoard gameMovesSearch::movesSearchEngine(gameBoard board) {
    char from[] = {'.','r','w','1','2','3','4','5','6','7'};
    char to[] = {'1','2','3','4','5','6','7','f'};
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 8; j++){
            board.addMove(from[i],to[j]);
        }
    }
    return gameBoard();
}
