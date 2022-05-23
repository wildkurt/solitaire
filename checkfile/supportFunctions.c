//
// Created by wendellbest on 3/8/22.
//
#include <stdio.h>
#include <string.h>
#include "check.h"

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
        case 'd' : return 1;
        case 'h' : return 1;
        case 'c' : return 1;
        case 's' : return 1;
        default: return 0;
    }
}

int rankValue(char c){
    switch(c){
        case 'A' : return 0;
        case '2' : return 1;
        case '3' : return 2;
        case '4' : return 3;
        case '5' : return 4;
        case '6' : return 5;
        case '7' : return 6;
        case '8' : return 7;
        case '9' : return 8;
        case 'T' : return 9;
        case 'J' : return 10;
        case 'Q' : return 11;
        case 'K' : return 12;
        default: return -1;
    }
}

char valueRank(int c){
    switch(c){
        case 0 : return 'A';
        case 1 : return '2';
        case 2 : return '3';
        case 3 : return '4';
        case 4 : return '5';
        case 5 : return '6';
        case 6 : return '7';
        case 7 : return '8';
        case 8 : return '9';
        case 9 : return 'T';
        case 10 : return 'J';
        case 11 : return 'Q';
        case 12 : return 'K';
        default : return '0';
    }
}

int findFoundations(char *buffer, FILE *input, int *line, Card *foundations){
    int j = 0;
    do{
        for(int i = 0; buffer[i] != '\n'; i++){
            if(isRank(buffer[i]) && isSuit(buffer[i+1])){
                foundations[j].rank = buffer[i];
                foundations[j].suit = buffer[i+1];
                foundations[j].stock = 'n';
                foundations[j].covered = 'n';
                foundations[j].waste = 'n';
                j++;
            }
            if(buffer[i] == '_' && isSuit(buffer[i+1])){
                foundations[j].rank = buffer[i];
                foundations[j].suit = buffer[i+1];
                foundations[j].stock = 'n';
                foundations[j].covered = 'n';
                foundations[j].waste = 'n';
                j++;
            }
        }
        if(strstr(buffer, "TABLEAU")!=0){
            if(j == 4){
                fputs(buffer, input);
                return 1;
            }
            else
                return 0;
        }
        *line = *line + 1;
    }while(fgets(buffer,50,input)!=0);
    if(j==4){
        return 1;
    }
    else
        return 0;
}

int findTableaus(FILE *input, int *line, Card *t7, Card *t6,
                 Card *t5, Card *t4, Card *t3,
                 Card *t2, Card *t1){
    char buffer[50]={0};
    int seven = 0, six = 0, five = 0, four = 0, three = 0, two = 0, one = 0, find, j, cover = 0;
    while(fgets(buffer, 50,  input)!=0){
        find = 0;
        cover = 0;
        j = 0;
        *line = *line + 1;
        if(strstr(buffer,"STOCK:")!=0){
            if(seven == 0 || six == 0 || five == 0 || four == 0 || three == 0 || two == 0 || one ==0){
                fprintf(stderr, "Did not find all tableaus\n");
                return 0;
            }
            else{
                fputs(buffer, input);
                return 1;
            }
        }
        for(int i = 0; buffer[i] != '\0'; i++){
            if(isRank(buffer[i]) && isSuit(buffer[i+1])) {
                find++;
                if (seven == 0) {
                    t7[j].rank = buffer[i];
                    t7[j].suit = buffer[i + 1];
                    if (cover == 0)
                        t7[j].covered = 'y';
                    else
                        t7[j].covered = 'n';
                    t7[j].stock = 'n';
                    t7[j].waste = 'n';
                    j++;
                }
                else if (six == 0) {
                    t6[j].rank = buffer[i];
                    t6[j].suit = buffer[i + 1];
                    if (cover == 0)
                        t6[j].covered = 'y';
                    else
                        t6[j].covered = 'n';
                    t6[j].stock = 'n';
                    t6[j].waste = 'n';
                    j++;
                }
                else if (five == 0) {
                    t5[j].rank = buffer[i];
                    t5[j].suit = buffer[i + 1];
                    if (cover == 0)
                        t5[j].covered = 'y';
                    else
                        t5[j].covered = 'n';
                    t5[j].stock = 'n';
                    t5[j].waste = 'n';
                    j++;
                }
                else if (four == 0) {
                    t4[j].rank = buffer[i];
                    t4[j].suit = buffer[i + 1];
                    if (cover == 0)
                        t4[j].covered = 'y';
                    else
                        t4[j].covered = 'n';
                    t4[j].stock = 'n';
                    t4[j].waste = 'n';
                    j++;
                }
                else if (three == 0) {
                    t3[j].rank = buffer[i];
                    t3[j].suit = buffer[i + 1];
                    if (cover == 0)
                        t3[j].covered = 'y';
                    else
                        t3[j].covered = 'n';
                    t3[j].stock = 'n';
                    t3[j].waste = 'n';
                    j++;
                }
                else if (two == 0) {
                    t2[j].rank = buffer[i];
                    t2[j].suit = buffer[i + 1];
                    if (cover == 0)
                        t2[j].covered = 'y';
                    else
                        t2[j].covered = 'n';
                    t2[j].stock = 'n';
                    t2[j].waste = 'n';
                    j++;
                }
                else if (one == 0) {
                    t1[j].rank = buffer[i];
                    t1[j].suit = buffer[i + 1];
                    if (cover == 0)
                        t1[j].covered = 'y';
                    else
                        t1[j].covered = 'n';
                    t1[j].stock = 'n';
                    t1[j].waste = 'n';
                    j++;
                }
            }
            if(buffer[i]=='|'){
                find++;
                if(seven == 0){
                    t7[j].rank = '|';
                    t7[j].suit = '0';
                    t7[j].covered = 'n';
                    t7[j].stock = 'n';
                    t7[j].waste = 'n';
                    cover = 1;
                    j++;
                }
                else if(six == 0){
                    t6[j].rank = '|';
                    t6[j].suit = '0';
                    t6[j].covered = 'n';
                    t6[j].stock = 'n';
                    t6[j].waste = 'n';
                    cover = 1;
                    j++;
                }
                else if(five == 0){
                    t5[j].rank = '|';
                    t5[j].suit = '0';
                    t5[j].covered = 'n';
                    t5[j].stock = 'n';
                    t5[j].waste = 'n';
                    cover = 1;
                    j++;
                }
                else if(four == 0){
                    t4[j].rank = '|';
                    t4[j].suit = '0';
                    t4[j].covered = 'n';
                    t4[j].stock = 'n';
                    t4[j].waste = 'n';
                    cover = 1;
                    j++;
                }
                else if(three == 0){
                    t3[j].rank = '|';
                    t3[j].suit = '0';
                    t3[j].covered = 'n';
                    t3[j].stock = 'n';
                    t3[j].waste = 'n';
                    cover = 1;
                    j++;
                }
                else if(two == 0){
                    t2[j].rank = '|';
                    t2[j].suit = '0';
                    t2[j].covered = 'n';
                    t2[j].stock = 'n';
                    t2[j].waste = 'n';
                    cover = 1;
                    j++;
                }
                else if(one == 0){
                    t1[j].rank = '|';
                    t1[j].suit = '0';
                    t1[j].covered = 'n';
                    t1[j].stock = 'n';
                    t1[j].waste = 'n';
                    cover = 1;
                    j++;
                }
            }
        }
        if(find > 0){
            if(seven == 0)
                seven++;
            else if(six == 0)
                six++;
            else if(five == 0)
                five++;
            else if(four == 0)
                four++;
            else if(three == 0)
                three++;
            else if (two == 0)
                two++;
            else if(one == 0)
                one++;
        }
        if(one == 1)
            return 1;
    }
}

int findStockWaste(char *buffer, FILE *input, int *line, Card *sw){
    int find = 0, stockFlip = 0, j = 0;

    do{
        if(strstr(buffer, "MOVES:")!=0 && strstr(buffer, "STOCK:")==0){
            if(find == 0){
                return 0;
            }
            else{
                fputs(buffer, input);
                return 1;
            }
        }
        for(int i = 0; buffer[i] != '\0'; i++){
            if(isRank(buffer[i]) && isSuit(buffer[i+1])){
                sw[j].rank = buffer[i];
                sw[j].suit = buffer[i+1];
                if(stockFlip == 0){
                    sw[j].waste = 'y';
                    sw[j].stock = 'n';
                }
                else{
                    sw[j].waste = 'n';
                    sw[j].stock = 'y';
                }
                sw[j].covered = 'n';
                j++;
                find++;
            }
            if(buffer[i] == '|'){
                sw[j].rank = buffer[i];
                sw[j].suit = '0';
                sw[j].covered = 'n';
                sw[j].waste = 'n';
                sw[j].stock = 'n';
                stockFlip++;
                j++;
                find++;
            }
        }
        if(strstr(buffer, "STOCK:")!= 0 && strstr(buffer, "MOVES:")!= 0)
            break;
        *line = *line + 1;
    }while(fgets(buffer, 50, input)!=0);
    if(find > 0)
        return 1;
}

void countCards(Card *foundations, int *club, int *diamond, int *heart,
                int *spade, Card *t7, Card *t6, Card *t5,
                Card *t4, Card *t3, Card *t2, Card *t1,
                Card *sw){
    int clubrank = rankValue(foundations[0].rank);
    int diamondrank = rankValue(foundations[1].rank);
    int heartrank = rankValue(foundations[2].rank);
    int spaderank = rankValue(foundations[3].rank);

    for(int i = 0; i <= clubrank; i++){
        club[i]++;
    }
    for(int i = 0; i <= diamondrank; i++){
        diamond[i]++;
    }
    for(int i = 0; i <= heartrank; i++){
        heart[i]++;
    }
    for(int i = 0; i <= spaderank; i++){
        spade[i]++;
    }
    for(int i = 0; i < 30; i++){
        if(t7[i].suit == 'c' && isRank(t7[i].rank))
            club[rankValue(t7[i].rank)]++;
        else if(t7[i].suit == 'd' && isRank(t7[i].rank))
            diamond[rankValue(t7[i].rank)]++;
        else if(t7[i].suit == 'h' && isRank(t7[i].rank))
            heart[rankValue(t7[i].rank)]++;
        else if(t7[i].suit == 's' && isRank(t7[i].rank))
            spade[rankValue(t7[i].rank)]++;
        if(t6[i].suit == 'c' && isRank(t6[i].rank))
            club[rankValue(t6[i].rank)]++;
        else if(t6[i].suit == 'd' && isRank(t6[i].rank))
            diamond[rankValue(t6[i].rank)]++;
        else if(t6[i].suit == 'h' && isRank(t6[i].rank))
            heart[rankValue(t6[i].rank)]++;
        else if(t6[i].suit == 's' && isRank(t6[i].rank))
            spade[rankValue(t6[i].rank)]++;
        if(t5[i].suit == 'c' && isRank(t5[i].rank))
            club[rankValue(t5[i].rank)]++;
        else if(t5[i].suit == 'd' && isRank(t5[i].rank))
            diamond[rankValue(t5[i].rank)]++;
        else if(t5[i].suit == 'h' && isRank(t5[i].rank))
            heart[rankValue(t5[i].rank)]++;
        else if(t5[i].suit == 's' && isRank(t5[i].rank))
            spade[rankValue(t5[i].rank)]++;
        if(t4[i].suit == 'c' && isRank(t4[i].rank))
            club[rankValue(t4[i].rank)]++;
        else if(t4[i].suit == 'd' && isRank(t4[i].rank))
            diamond[rankValue(t4[i].rank)]++;
        else if(t4[i].suit == 'h' && isRank(t4[i].rank))
            heart[rankValue(t4[i].rank)]++;
        else if(t4[i].suit == 's' && isRank(t4[i].rank))
            spade[rankValue(t4[i].rank)]++;
        if(t3[i].suit == 'c' && isRank(t3[i].rank))
            club[rankValue(t3[i].rank)]++;
        else if(t3[i].suit == 'd' && isRank(t3[i].rank))
            diamond[rankValue(t3[i].rank)]++;
        else if(t3[i].suit == 'h' && isRank(t3[i].rank))
            heart[rankValue(t3[i].rank)]++;
        else if(t3[i].suit == 's' && isRank(t3[i].rank))
            spade[rankValue(t3[i].rank)]++;
        if(t2[i].suit == 'c' && isRank(t2[i].rank))
            club[rankValue(t2[i].rank)]++;
        else if(t2[i].suit == 'd' && isRank(t2[i].rank))
            diamond[rankValue(t2[i].rank)]++;
        else if(t2[i].suit == 'h' && isRank(t2[i].rank))
            heart[rankValue(t2[i].rank)]++;
        else if(t2[i].suit == 's' && isRank(t2[i].rank))
            spade[rankValue(t2[i].rank)]++;
        if(t1[i].suit == 'c' && isRank(t1[i].rank))
            club[rankValue(t1[i].rank)]++;
        else if(t1[i].suit == 'd' && isRank(t1[i].rank))
            diamond[rankValue(t1[i].rank)]++;
        else if(t1[i].suit == 'h' && isRank(t1[i].rank))
            heart[rankValue(t1[i].rank)]++;
        else if(t1[i].suit == 's' && isRank(t1[i].rank))
            spade[rankValue(t1[i].rank)]++;
        if(sw[i].suit == 'c' && isRank(sw[i].rank))
            club[rankValue(sw[i].rank)]++;
        else if(sw[i].suit == 'd' && isRank(sw[i].rank))
            diamond[rankValue(sw[i].rank)]++;
        else if(sw[i].suit == 'h' && isRank(sw[i].rank))
            heart[rankValue(sw[i].rank)]++;
        else if(sw[i].suit == 's' && isRank(sw[i].rank))
            spade[rankValue(sw[i].rank)]++;
    }
}

void printCards(Card *arr, int size){
    for(int i = 0; i < size; i++){
        if(arr[i].rank != 0){
            if(arr[i].rank == '|')
                printf("%c ", arr[i].rank);
            else
                printf("%c%c ",arr[i].rank, arr[i].suit);
        }
    }
    printf("\n");
}

int iterateTableaus(Card *ptr){
    while(ptr->rank != '|'){
        ptr++;
    }
    while(ptr->rank != '\0'){
        if((ptr+1)->rank == '\0'){
            return 0;
        }
        else if(isRedOrBlack(ptr->suit)== isRedOrBlack((ptr+1)->suit)){
            return 1;
        }
        ptr++;
    }
}

char isRedOrBlack(char c){
    if(c == 'd' || c == 'h')
        return 'r';
    else if(c == 'c' || c == 's')
        return 'b';
}

int checkTableaus(Card *t7, Card *t6, Card *t5, Card *t4,
                  Card *t3, Card *t2, Card *t1){
    Card *ptr;
    ptr = t7;
    if(iterateTableaus(ptr)){
        return 1;
    }
    ptr = t6;
    if(iterateTableaus(ptr)){
        return 1;
    }
    ptr = t5;
    if(iterateTableaus(ptr)){
        return 1;
    }
    ptr = t4;
    if(iterateTableaus(ptr)){
        return 1;
    }
    ptr = t3;
    if(iterateTableaus(ptr)){
        return 1;
    }
    ptr = t2;
    if(iterateTableaus(ptr)){
        return 1;
    }
    ptr = t1;
    if(iterateTableaus(ptr)){
        return 1;
    }
}
