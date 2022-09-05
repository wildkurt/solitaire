//
// Created by wendellbest on 9/4/22.
//

#ifndef SOLITAIRE_GAMEMOVESSEARCH_H
#define SOLITAIRE_GAMEMOVESSEARCH_H


#include "gameBoard.h"
#include "searchParameters.h"

class gameMovesSearch {
private:
    gameBoard board;
    searchParameters search;
public:
    gameMovesSearch(searchParameters search, gameBoard board) { this->search = search; this->board = board;}
    gameBoard movesSearchEngine(gameBoard board);
};


#endif //SOLITAIRE_GAMEMOVESSEARCH_H
