//
// Created by wendellbest on 2/14/24.
//

#include <string.h>
#include <stdlib.h>
#include "advance.h"

void getCommandLineArguments(int args,char **argv, AdvanceArgs *arguments){
    for(int i = 0; i < args; i++){
        if(strstr(argv[i],"-m")!=0){
            arguments->movesLimit = 't';
            arguments->numberToPlay = atoi(argv[i+1]);
            i+=2;
        }
        else if(strstr(argv[i],"-o")!=0){
            int length = (int)strlen(argv[i+1]);
            arguments->outputToFile = (char) malloc((length + 1) * sizeof(char));
            strcpy(arguments->outputfile, argv[i+1]);
            i+=2;
        }
        else if(strstr(argv[i], "-x")!=0){
            arguments->exchangeFormat = 't';
        }
        else{
            int length = (int)strlen(argv[i]);
            arguments->inputfile = malloc((length + 1) * sizeof(char));
            strcpy(arguments->inputfile, argv[i]);
        }
    }
}

void writeSTDINtoFile(AdvanceArgs *arguments){

}