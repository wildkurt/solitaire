//
// Created by wendellbest on 7/7/22.
//

#include "gameTableau.h"
#include <fstream>

void gameTableau::getTableau(std::__cxx11::basic_string<char> basicString) {
    filename = basicString;
    std::ifstream input;
    input.open(filename,std::ios_base::in);
    std::string buffer;
}
