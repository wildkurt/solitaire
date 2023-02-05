//
// Created by wendellbest on 1/15/23.
//

#include <iostream>
#include "Moves.h"

Moves::Moves(const Moves &omoves) {
    this->moves = omoves.moves;
}

Moves &Moves::operator=(const Moves &omoves) {
    this->moves = omoves.moves;
    return *this;
}

void Moves::addMove(Move move) {
    moves.push_back(move);
}

Move Moves::getMoves() {
    return Move();
}

void Moves::printMoves() {
    std::cout<< std::endl;
    std::cout << "Moves: ";
    for(std::vector<Move>::iterator itr = moves.begin(); itr != moves.end(); itr++){
        if(Move::isMove(itr->getFrom(),itr->getTo()))
            std::cout << itr->getFrom() << "->" << itr->getTo() << " ";
        else if(Move::isStockMove(itr->getFrom()))
            std::cout << itr->getFrom() << " ";
    }
    std::cout << std::endl;
}
// Characters are "1, 2, 3, 4, 5, 6, 7, . , r, w, f"
long int Moves::buildGameConfigNumber() {
    std::string strNumber = "";
    if(moves.empty())
        return 0;
    for(std::vector<Move>::iterator itr = moves.begin(); itr != moves.end(); itr++){
        if(itr->isMove(itr->getFrom(), itr->getTo())){
            char from = itr->getFrom();
            char to = itr->getTo();
            strNumber.append(moveString(&from,&to));
        }
    }
    return std::stol(strNumber);
}

std::string Moves::moveString(char *from, char *to) {
    std::string temp = "";
    if(*to == 'n'){
        if(*from == '.')
            return "8";
        else if(*from == 'r')
            return "9";
    }
    else if(*to == 'f'){
        if(*from == 'w'){
            temp.append("10");
            temp.append("11");
        }
        else{
            temp.append(from);
            temp.append("11");
        }
    }
    else{
       if(*from == 'w'){
           temp.append("10");
           temp.append(to);
       }
       else{
           temp.append(from);
           temp.append(to);
       }
    }
    return temp;
}


