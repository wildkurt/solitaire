//
// Created by wendellbest on 7/7/22.
//

#ifndef SOLITAIRE_GAMEFOUNDATIONS_H
#define SOLITAIRE_GAMEFOUNDATIONS_H

#include <string>
#include "card.h"

class gameFoundations {
private:
    card fnd[4];
    std::string filename;
public:
    void getFoundation(std::__cxx11::basic_string<char> basicString);
    void printFoundation();
};


#endif //SOLITAIRE_GAMEFOUNDATIONS_H
