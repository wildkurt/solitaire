//
// Created by wendellbest on 1/29/24.
//

#include <stdio.h>
#include <string.h>
#include "check.h"

int getGameFile(GameConfiguration *game, char *filename){
    int result = 0, line = 1;
    FILE *filelink = 0;
    char buffer[MAX_BUFFER];

    if(strlen(filename) <=0){
        filelink = fopen(stdin,"r");
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
    return 1;
}


