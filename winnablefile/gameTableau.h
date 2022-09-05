//
// Created by wendellbest on 7/7/22.
//

#ifndef SOLITAIRE_GAMETABLEAU_H
#define SOLITAIRE_GAMETABLEAU_H


#include <string>
#include <vector>
#include "card.h"

class gameTableau {
private:
    std::string filename;
    std::vector <card> col7;
    std::vector <card> col6;
    std::vector <card> col5;
    std::vector <card> col4;
    std::vector <card> col3;
    std::vector <card> col2;
    std::vector <card> col1;

public:
    gameTableau()= default;
    gameTableau(const gameTableau &old);
    gameTableau& operator=(const gameTableau &old);
    ~gameTableau()= default;
    void getTableau(std::__cxx11::basic_string<char> basicString);
    void printTableau();
    void addCardsToColumn(int columns, card newCard);
    bool columnFilled(int columns);
    void printColumn(int i);
    std::vector<card> getColPtr(int i);
    bool winningConfigTableau();
};


#endif //SOLITAIRE_GAMETABLEAU_H
