//
// Created by wende on 5/30/2022.
//
#include <stdio.h>
#include <string.h>
#include "check.h"
#include "foundation.h"
#include "tableau.h"
#include "stockWaste.h"
/** The main program will open the file then parse it to find all
 * the required elements. During parsing, it calls functions that
 * will determine if there is a element present and will also
 * check the tableaus for a legal order. Foundations will be checked
 * for correct suits. It will then initiate a count of covered cards
 * and cards in the stock and waste*/
int main(int args, char *argv[]){
    FILE *input;
    char buffer[50];
    Rules rules;
    char *lim;
    int found = 0, line = 0, covered = 0, stock = 0, waste = 0;

    if(args < 2){
        input = fopen((const char *) stdin, "r");
    }
    else{
        input = fopen(argv[1], "r");
    }
    if(input == 0){
        fprintf(stderr, "Unable to open file %s\n", argv[1]);
        return 1;
    }
    while(fgets(buffer, 50, input) != 0){
        line++;
        if(buffer[0] == '#')
            continue;
        if(strstr(buffer, "RULES:") != 0){
            found++;
        }
        if(strstr(buffer, "turn 1") != 0){
            if(found < 1){ //1 if RULES: found
                fprintf(stderr,"Rules not found line %d\n", line);
                return 1;
            }
            rules.turnOver = 1;
            found++;
        }
        if(strstr(buffer, "turn 3") != 0){
            if(found < 1){ //1 if RULES: found
                fprintf(stderr,"Rules not found line %d\n", line);
                return 1;
            }
            rules.turnOver = 3;
            found++;
        }
        if(strstr(buffer, "unlimited") != 0){
            if(found < 2){ //2 if turns found
                fprintf(stderr,"Turn not found line %d\n", line);
                return 1;
            }
            rules.limit = -1;
            found++;
        }
        lim = strstr(buffer, "limit ");
        if(lim != 0){
            if(found < 2){ //2 if turns found
                fprintf(stderr,"Turn not found line %d\n", line);
                return 1;
            }
            int bob = 0;
            char string[10];
            sscanf(lim,"%s %d", string, &bob);
            rules.limit = bob;
            found++;
        }
        if(strstr(buffer, "FOUNDATIONS:") != 0){
            if(found < 3){ // 3 if limits found
                fprintf(stderr,"Limit not found line %d\n", line);
                return 1;
            }
            found++;
            if(!findFoundations(buffer, input, &line)){
                fprintf(stderr,"Foundations are incorrect or incomplete line %d\n", line);
                return 1;
            }
            //printFoundation();
            found++;
        }
        if(strstr(buffer, "TABLEAU:") != 0){
            if(found < 5){ // 5 if TABLEAU: and the tableaus found
                fprintf(stderr,"Foundations not found line %d\n", line);
                return 1;
            }
            found++;
            if(!findTableau(buffer, input, &line)){
                fprintf(stderr, "TABLEAU: not found or tableau is incorrect line %d\n",line);
                return 1;
            }
            //printTableau();
            found++;
        }
        if(strstr(buffer, "STOCK:") != 0){
            if(found < 7){
                fprintf(stderr, "TABLEAU: not found or tableau is incorrect line %d\n",line);
                return 1;
            }
            found++;
            if(!findStockWaste(buffer, input, &line)){
                fprintf(stderr, "Stock not found or stock is incorrect line %d\n",line);
                return 1;
            }
            //printStockWaste();
            found++;
        }
        if(strstr(buffer, "MOVES:") != 0){
            found++;
            break;
        }
        memset(buffer,0,50);
    }
    if(found == 10){
        printf("File is valid\n");
    }
    countCards(&covered, &stock, &waste);
    printf("%d covered cards\n", covered);
    printf("%d stock cards\n", stock);
    printf("%d waste cards\n", waste);

    fclose(input);
    return 0;
}