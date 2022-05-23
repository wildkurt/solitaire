//
// Created by wendellbest on 5/19/22.
//

#include "foundations.h"
/**Case a: The initial foundation is empty
 * Case 1a: the rank is '_' and there is a suit
 * Case b: the foundation is not empty
 * Case b1: need to make sure the card on the foundation
 * is one less than the card being added*/
bool foundations::addCardToFoundation(Card n) {

    for(int i = 0; i < 4; i++){
        if(n.getRank() == '_'){
            switch(n.getSuit()){
                case 'c' : foundation[0] = n; break;
                case 'd' : foundation[1] = n; break;
                case 'h' : foundation[2] = n; break;
                case 's' : foundation[3] = n; break;
                default: return false;
            }
            return true;
        }
        else{
            int index = 0;
            switch(n.getSuit()){
                case 'c' : index = 0; break;
                case 'd' : index = 1; break;
                case 'h' : index = 2; break;
                case 's' : index = 3; break;
                default: return false;
            }
            if(foundation[index].getRankValue() + 1 == n.getRankValue()){
                foundation[index] = n;
            }
        }
    }
    return false;
}

bool foundations::isFoundationFull(){
    bool result = true;
    for(int i = 0; i < 4; i++){
        if(foundation[i].getSuit() == '_' ){
            result = false;
            break;
        }
    }
    return result;
}
