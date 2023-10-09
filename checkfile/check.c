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
void readFile(char *file, Rules *rules);

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
    /*This function checks for missing and/or duplicate cards.
     * It will work even if there are duplicate and missing cards
     * at the same time. Keeps everything below it from printing if
     * true(1)*/
    //Checks to see if everything was found
    if(rules.found == 10){
        printf("File is valid\n");
    }
    else{
        fprintf(stderr, "File is invalid at line %d\n", rules.line);
        return 1;
    }
    //Counts the covered, stock, and waste cards
    if(missingDuplicateCards()){
        return 1;
    }
    countCards(&covered, &stock, &waste);
    printf("%d covered cards\n", covered);
    printf("%d stock cards\n", stock);
    printf("%d waste cards\n", waste);
    printf("\n");

    return 0;
}

void readFile(char *file, Rules *rules){
    FILE *input;
    char buffer[MAX_BUFFER], readBuffer[MAX_BUFFER];
    char *lim;
    int found = 0, line = 0, index = 0 ;

    input = fopen(file,"r");

    if(input == 0){
        fprintf(stderr, "Unable to open %s", file);
    }

    while(fgets(buffer, MAX_BUFFER, input) != 0){
        line++;
        //Ignore hashes
        for(int i = 0; i < MAX_BUFFER; i++){
            if(buffer[i] != '#' && buffer[i] != '\0'){
                readBuffer[index++] = buffer[i];
            }
            else{
                index = 0;
                break;
            }
        }
            //RULES:
        if(strstr(readBuffer, "RULES:") != 0){
            found++;
        }
        //I made a Rules struct, not necessary for check, but trying to lean forward
        //Checks for Turn 1 or Turn 3
        if(strstr(readBuffer, "turn 1") != 0){
            if(found < 1){ //1 if RULES: found
                fprintf(stderr,"Rules not found line %d\n", line);
                rules->line = line;
                rules->found = found;
        }
        rules->turnOver = 1;
        found++;
        }
        if(strstr(readBuffer, "turn 3") != 0){
            if(found < 1){ //1 if RULES: found
                fprintf(stderr,"Rules not found line %d\n", line);
                rules->line = line;
                rules->found = found;
                            }
            rules->turnOver = 3;
            found++;
        }
        //Checks for limit N or unlimited
        if(strstr(readBuffer, "unlimited") != 0){
            if(found < 2){ //2 if turns found
                fprintf(stderr,"Turn not found or incorrect line %d\n", line);
                rules->line = line;
                rules->found = found;
            }
            rules->limit = -1;
            found++;
        }
        //I needed to do it this way so I could use scanf to get the number from the
        //string, and if the number is bigger than one digit.
        lim = strstr(readBuffer, "limit ");
        if(lim != 0){
            if(found < 2){ //2 if turns found
                fprintf(stderr,"Turn not found line %d\n", line);
                rules->line = line;
                rules->found = found;
            }
            int bob = 0;
            char string[10];
            sscanf(lim,"%s %d", string, &bob);
            rules->limit = bob;
            found++;
        }
        //Foundations
        if(strstr(readBuffer, "FOUNDATIONS:") != 0){
            if(found < 3){ // 3 if limits found
                fprintf(stderr,"Limit not found line %d\n", line);
                rules->line = line;
                rules->found = found;
            }
            found++;
            //This is where the foundations functions take over
            if(!findFoundations(readBuffer, input, &line)){
                fprintf(stderr,"Foundations are incorrect or incomplete line %d\n", line);
                rules->line = line;
                rules->found = found;
            }
            //printFoundation();
            found++;
        }
        //Tableau
        if(strstr(readBuffer, "TABLEAU:") != 0){
            if(found < 5){ // 5 if TABLEAU: and the tableaus found
                fprintf(stderr,"Foundations not found line %d\n", line);
                rules->line = line;
                rules->found = found;
            }
            found++;
            if(!findTableau(readBuffer, input, &line)){
                fprintf(stderr, "TABLEAU: not found or tableau is incorrect line %d\n",line);
                printTableau();
                rules->line = line;
                rules->found = found;
            }

            found++;
        }
        //STOCK:
        if(strstr(readBuffer, "STOCK:") != 0){
            if(found < 7){
                fprintf(stderr, "TABLEAU: not found or tableau is incorrect line %d\n",line);
                rules->line = line;
                rules->found = found;
            }
            found++;
            if(!findStockWaste(readBuffer, input, &line)){
                fprintf(stderr, "Stock not found or stock is incorrect line %d\n",line);
                rules->line = line;
                rules->found = found;
            }
            //printStockWaste();
            found++;
        }
        //MOVES:
        if(strstr(readBuffer, "MOVES:") != 0){
            found++;
            break;
        }
        memset(buffer,0,MAX_BUFFER);
        memset(readBuffer,0,MAX_BUFFER);
    }
    rules->line = line;
    rules->found = found;
    fclose(input);
}