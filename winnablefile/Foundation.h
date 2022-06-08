//
// Created by wende on 6/7/2022.
//

#ifndef SOLITAIRE_FOUNDATION_H
#define SOLITAIRE_FOUNDATION_H

#include "Card.h"
#include <string>

class Foundation {
private:
    Card fd[4];
public:
    Foundation()=default;
    Foundation(Foundation &foundation);
    void addCardToFoundation(Card card);
    Foundation getFoundation(std::string inputfilename);
    bool isFoundationFilled();
};


#endif //SOLITAIRE_FOUNDATION_H
