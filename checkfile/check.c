//
// Created by wende on 5/30/2022.
//
#include <stdio.h>
#include "check.h"
/** The main program will open the file then parse it to find all
 * the required elements. During parsing, it calls functions that
 * will determine if there is a element present and will also
 * check the tableaus for a legal order. Foundations will be checked
 * for correct suits. It will then initiate a count of covered cards
 * and cards in the stock and waste*/


int main(int args, char *argv[]){
    Rules rules = {0,0,0,0};
    int covered = 0, stock = 0, waste = 0;
    //This section is for getting the command line arguments and
    //opening a file pointer.
    if(args < 2){
        readFile("", &rules);
    }
    else{
        readFile(argv[1], &rules);
    }
    //Look for missing cards
    if(missingDuplicateCards()){
        return 1;
    }
    if(rules.found == 10){
        printf("Input file is valid\n");
    }
    else{
        fprintf(stderr, "File is invalid at line %d\n", rules.line);
        return 1;
    }
    countCards(&covered, &stock, &waste);
    printf("%d covered cards\n", covered);
    printf("%d stock cards\n", stock);
    printf("%d waste cards\n", waste);
    printf("\n");

    return 0;
}

