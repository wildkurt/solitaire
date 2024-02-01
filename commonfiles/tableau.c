//
// Created by wendellbest on 1/29/24.
//

#include <string.h>
#include "tableau.h"

/**For this part of the file, the columns will always be below the TABLEAU: header. Will need
 * to make sure that the cards for each line are put in the correct columns. Need to account for the '|' which is the
 * indicator that the cards following are face up. Foundations will exit once the last foundation block is found, so
 * still need to find the TABLEAU: header**/



int getTableau(Tableau *tableau, int *line, FILE *filelink, char *buffer){
    char cleanBuffer[MAX_BUFFER] = {0};
    int column = 7;
    while(fgets(buffer, MAX_BUFFER, filelink)) {
        for(int i = 0; i < MAX_BUFFER && buffer[i] != '#' && buffer[i] != '\0'; i++){
            cleanBuffer[i] = buffer[i];
        }
        Card *ptr = getPointerToColumn(column, tableau);
        if(strstr(cleanBuffer, "TABLEAU:")!=0){
            continue;
        }
        for(int i = 0; i < MAX_BUFFER && cleanBuffer[i] != '\0'; i++){

        }
    }
    return 0;
}

Card *getPointerToColumn(int column, Tableau *tableau){
    switch(column){
        case 1 : return tableau->tab1;
        case 2 : return tableau->tab2;
        case 3 : return tableau->tab3;
        case 4 : return tableau->tab4;
        case 5 : return tableau->tab5;
        case 6 : return tableau->tab6;
        case 7 : return tableau->tab7;
    }
}