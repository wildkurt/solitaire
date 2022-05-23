//
// Created by wendellbest on 3/8/22.
//

#include <iostream>
#include <string.h>
#include "switches.h"
#include "gameConfiguration.h"

/**The main program will receive the name of the input file and */
int main(int args, char *argv[]){
    std::string filename;
    Switches inputSwitches;
    if(args < 2){
        std::cin >> filename;
    }
    else{
        for(int i = 1; i < args; i++){
            if(strcmp(argv[i],"-m") == 0){
                inputSwitches.setLimitedMoves('y');
                inputSwitches.setNumberOfMoves(std::stoi(argv[++i]));
            }
            else if(strcmp(argv[i],"-c") == 0){
                inputSwitches.setHashTable('y');
            }
            else if(strcmp(argv[i],"-f") == 0){
                inputSwitches.setSafeMoves('y');
            }
            else if(strcmp(argv[i], "-v") == 0){
                inputSwitches.setVerboseMode('y');
            }
            else{
                inputSwitches.setInputFileName(argv[i]);
            }
        }
    }
    int number = 0;
    number = system("./check input.txt");
    std::cout << "Returned " << number << std::endl;
    GameConfiguration game(inputSwitches);
    game.printCardArrays();
    return 0;
}