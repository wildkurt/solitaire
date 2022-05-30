//
// Created by wende on 5/30/2022.
//

#include "card.h"
int isRank(char c){
    switch(c){
        case 'A' : return 1;
        case '2' : return 1;
        case '3' : return 1;
        case '4' : return 1;
        case '5' : return 1;
        case '6' : return 1;
        case '7' : return 1;
        case '8' : return 1;
        case '9' : return 1;
        case 'T' : return 1;
        case 'J' : return 1;
        case 'Q' : return 1;
        case 'K' : return 1;
        default: return 0;
    }
}

int isSuit(char c){
    switch(c){
        case 'c' : return 1;
        case 'd' : return 1;
        case 'h' : return 1;
        case 's' : return 1;
        default: return 0;
    }
}

char isRedOrBlack(char c){
    switch(c){
        case 'c' : return 'b';
        case 'd' : return 'r';
        case 'h' : return 'r';
        case 's' : return 'b';
    }
}