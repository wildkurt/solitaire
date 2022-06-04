//
// Created by wendellbest on 6/4/22.
//

#include "printGameToFile.h"
#include <stdio.h>
#include <stdlib.h>
#include "../checkfile/foundation.h"
#include "../checkfile/tableau.h"
#include "../checkfile/stockWaste.h"

void printGameToFile(Rules *rules, GameConfiguration *gameconfiguration){
    FILE *output;
    output = fopen(gameconfiguration->filename, "w");
    if(output == '\0'){
        fprintf(stderr,"Unable to write to %s\n", gameconfiguration->filename);
        exit(1);
    }
    fprintf(output,"RULES:\n");
    if(rules->turnOver == 3){
        fprintf(output, "turn 3\n");
    }
    else{
        fprintf(output,"turn 1\n");
    }
    if(rules->limit == -1){
        fprintf(output,"unlimited\n");
    }
    else{
        fprintf(output,"limit %d\n", rules->limit);
    }
    fprintf(output,"FOUNDATIONS:\n");
    Card *fdptr = fdPtr();
    for(int i = 0; i < 4; i++){
        fprintf(output,"%c%c ", fdptr[i].rank, fdptr[i].suit);
    }
    fprintf(output,"\n");
    fprintf(output,"TABLEAU:\n");
    Card *tabptr;
    int col = 7;
    while(col != 0){
        tabptr = setPointer(col);
        while(tabptr->rank != '\0'){
            if(tabptr->rank == '|')
                fprintf(output,"%c", tabptr->rank);
            else
                fprintf(output,"%c%c ",tabptr->rank, tabptr->suit);
            tabptr++;
        }
        fprintf(output,"\n");
        col--;
    }
    fprintf(output,"STOCK:\n");
    Card *swptr = stockWastePtr();
    while(swptr->rank != '\0'){
        if(swptr->rank == '|')
            fprintf(output, "%c ", swptr->rank);
        else
            fprintf(output, "%c%c ", swptr->rank, swptr->suit);
        swptr++;
    }
    fprintf(output, "\n");
    fprintf(output,"MOVES:\n");
    fclose(output);
}