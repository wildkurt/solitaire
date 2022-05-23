//
// Created by wendellbest on 3/8/22.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "check.h"

Card foundations[4];
Card t7[30];
Card t6[30];
Card t5[30];
Card t4[30];
Card t3[30];
Card t2[30];
Card t1[30];
Card sw[30];
int heart[13];
int diamond[13];
int club[13];
int spade[13];

int main(int args, char *argv[]){
    FILE *input = 0;
    char buffer[50]={0};
    int numTurns = 0, numLimits = 0, line = 0,found = 0, l = 0, covered = 0, stock = 0, waste = 0;
    char *numTurnsPtr, *numLimitsPtr;
    Card missing[52] = {0};
    Card duplicate[52] = {0};

    if(args == 1){
        input = stdin;
    }
    else{
        input = fopen(argv[1],"r");
    }
    if(input == 0){
        fprintf(stderr, "File %s not found\n",argv[1]);
        exit(1);
    }
    while(fgets(buffer, 50, input)!=0){
        line++;
        if(strstr(buffer, "RULES:")!=0)
            found++;
        if((numTurnsPtr=strstr(buffer, "turn"))!=0){
            if(found < 1){
                fprintf(stderr, "Expected RULES: at line %d\n", line);
                exit(1);
            }
            found++;
            sscanf(numTurnsPtr, "%*s %d", &numTurns);
            if(numTurns < 1 || (numTurns > 1 && numTurns < 3) || numTurns > 3){
                fprintf(stderr, "%d is invlaid, turnover must be 1 or 3\n", numTurns);
                exit(1);
            }
        }
        if((numLimitsPtr = strstr(buffer,"limit ")) != 0){
            if(found < 2){
                fprintf(stderr, "Expected \"turn\" at line %d\n", line);
                exit(1);
            }
            found++;
            sscanf(numLimitsPtr, "%*s %d", &numLimits);
        }
        if(strstr(buffer, "unlimited") != 0){
            if(found < 2){
                fprintf(stderr, "Expected \"turn\" at line %d\n", line);
                exit(1);
            }
            found++;
        }
        if(strstr(buffer, "FOUNDATIONS:") != 0){
            if(found < 3){
                fprintf(stderr, "Expected \"limit\" or \"unlimited\" at line %d\n", line);
                exit(1);
            }
            found++;
            if(findFoundations(buffer, input, &line, foundations)==1){
                found++;
            }
            else{
                fprintf(stderr,"Foundation cards not found line %d\n", line);
                exit(1);
            }
            if(foundations[0].suit != 'c' && foundations[1].suit != 'd' && foundations[2].suit != 'h' && foundations[3].suit != 's'){
                fprintf(stderr, "Foundations have the wrong suits at line %d\n",line);
                exit(1);
            }
        }
        if(strstr(buffer, "TABLEAU:") !=0){
            if(found < 5){
                fprintf(stderr, "Expected FOUNDATIONS: at line %d\n", line);
                exit(1);
            }
            found++;
            if(findTableaus(input, &line, t7, t6, t5, t4, t3, t2, t1) != 1) {
                fprintf(stderr, "Expected Tableau columns at line %d\n", line);
                exit(1);
            }
            else
                found++;
        }
        if(strstr(buffer, "STOCK:") != 0){
            if(found < 7){
                fprintf(stderr,"Did not find Tableau cards at line %d\n", line);
                exit(1);
            }
            found++;
            if(findStockWaste(buffer, input, &line, sw) == 1){
                found++;
            }
            else{
                fprintf(stderr,"Didn't find stock or waste cards at line %d\n", line);
                exit(1);
            }
        }
        if(strstr(buffer,"MOVES:")!=0){
            if(found < 9){
                fprintf(stderr, "Expected STOCK: at line %d\n", line);
                exit(1);
            }
            found++;
            //printf("MOVES:\n");
        }
    }
    rewind(input);
    countCards(foundations, club, diamond, heart, spade, t7, t6, t5, t4, t3, t2, t1, sw);
    if(checkTableaus(t7, t6, t5, t4, t3, t2, t1)){
        fprintf(stderr, "Tableaus are illegal\n");
        exit(1);
    }

    for(int i = 0; i <=12; i++){
        if(club[i]==0){
            missing[l].rank = valueRank(i);
            missing[l].suit = 'c';
            l++;
        }
        if(diamond[i]==0){
            missing[l].rank = valueRank(i);
            missing[l].suit = 'c';
            l++;
        }
        if(heart[i]==0){
            missing[l].rank = valueRank(i);
            missing[l].suit = 'c';
            l++;
        }
        if(spade[i]==0){
            missing[l].rank = valueRank(i);
            missing[l].suit = 'c';
            l++;
        }
    }
    if(l > 0){
        printf("The following cards are missing\n");
        printCards(missing,52);
        exit(1);
    }

    l=0;
    for(int i = 0; i <= 12; i++){
        if(club[i]>1) {
            duplicate[l].rank = valueRank(i);
            duplicate[l].suit = 'c';
            l++;
        }
        if(diamond[i]>1){
            duplicate[l].rank = valueRank(i);
            duplicate[l].suit = 'd';
            l++;
        }
        if(heart[i]>1){
            duplicate[l].rank = valueRank(i);
            duplicate[l].suit = 'h';
            l++;
        }
        if(spade[i]>1){
            duplicate[l].rank = valueRank(i);
            duplicate[l].suit = 's';
            l++;
        }
    }
    if(l > 0){
        printf("These cards are duplicates\n");
        printCards(duplicate, 52);
        exit(1);
    }

    for(int i = 0; i < 30; i++){
        if(t7[i].covered == 'y')
            covered++;
        if(t6[i].covered == 'y')
            covered++;
        if(t5[i].covered == 'y')
            covered++;
        if(t4[i].covered == 'y')
            covered++;
        if(t3[i].covered == 'y')
            covered++;
        if(t2[i].covered == 'y')
            covered++;
        if(t1[i].covered == 'y')
            covered++;
        if(sw[i].stock == 'y')
            stock++;
        if(sw[i].waste == 'y')
            waste++;
    }
    if(found == 10){
        printf("Input file is valid\n");
        printf("%d covered cards\n", covered);
        printf("%d stock cards\n", stock);
        printf("%d waste cards\n", waste);
        printf("\n");
    }
    else{
        fprintf(stderr,"Expected MOVES: at line %d\n", line);
        exit(1);
    }
    return 0;
}