//
// Created by wendellbest on 1/29/24.
//

#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "check.h"

int getGameFile(GameConfiguration *game, char *filename){
    int result = 0, line = 1;
    FILE *filelink = 0;
    char buffer[MAX_BUFFER];
    //No filename from command line
    if(filename==0){
        //Check to see if there is anything coming from stdin by checking if it is blocking for five seconds. If stdin
        //unblocks, then there is input, if not, then nothing is being piped in
        fd_set rfds;
        struct timeval tv;
        int retval;
        //initialize rfds
        FD_ZERO(&rfds);
        //set rfds to stdin file descriptor (0 = stdin, 1 = stdout, 3 - stderr)
        FD_SET(0,&rfds);
        //Set the seconds and nanoseconds for tv
        tv.tv_sec = 5;
        tv.tv_usec = 0;
        //See if stdin is unblocked, wait five seconds if not
        retval = select(1, &rfds, NULL, NULL, &tv);
        if(retval){
            filelink = stdin;
        }
        else{
            fprintf(stderr,"No input from stdin provided.\n");
            return 0;
        }
    }
    else{
        filelink = fopen(filename,"r");
    }
    if(filelink == 0){
        fprintf(stderr,"Unable to find file %s\n", filename);
        return 0;
    }
    result = getRules(&game->rules, &line, filelink, buffer);
    switch(result){
        case 1 : fprintf(stderr,"Error near line %d: expecting 'RULES:", line); return 0;
        case 2 : fprintf(stderr,"Error near line %d: expecting 'turn 1' or 'turn 3'", line); return 0;
        case 3 : fprintf(stderr,"Error near line %d: expecting 'limit N' or 'unlimited'", line); return 0;
        default : break;
    }
    result = getFoundations(&game->foundation, &line, filelink, buffer);
    switch(result){
        case 1 : fprintf(stderr, "Error near line %d: expecting 'FOUNDATIONS:'", line); return 0;
        case 2 : fprintf(stderr, "Error near line %d: Foundation suits are in incorrect order", line); return 0;
        case 3 : fprintf(stderr, "Error near line %d: Foundations not found", line); return 0;
        default : break;
    }
    result = getTableau(&game->tableau, &line, filelink, buffer);
    switch(result){
        case 1 : fprintf(stderr, "Error near line %d: Tableau Column order incorrect", line); return 0;
        case 2 : fprintf(stderr, "Error near line %d: Tableau is missing columns", line); return 0;
        default : break;
    }
    result = getStockWaste(&game->stockwaste, &line, filelink, buffer);
    switch(result){
        case 1 : fprintf(stderr, "Error near line %d: Stock not found", line); return 0;
        default : break;
    }
    fclose(filelink);
    return 1;
}

int countCards(GameConfiguration *game, int *covered, int *stock, int *waste){
    Card countingdeck[52] = {0};

    countFoundationCards(&game->foundation, countingdeck);
    countTableauCards(&game->tableau, countingdeck);
    countStockWasteCards(&game->stockwaste, countingdeck);
    return 0;
}