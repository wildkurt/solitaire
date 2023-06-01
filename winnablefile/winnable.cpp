//
// Created by wendellbest on 3/18/23.
//
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "SearchSettings.h"
#include "parseFile.h"

int main(int argc, char **argv){
    SearchSettings settings;
    GameConfiguration game;
    std::string command = "./cmake-build-debug/advance -x ";
    //std::string command = "/home/wendellbest/Documents/my-c-and-c-plus-plus-projects/Solitaire/cmake-build-debug/advance -x -o output.txt ";
    int systemResult = 0;

    //get the settings
    settings.getSettingsFromCL(argc, argv);
    //use advance to check the file
    command.append(settings.getFilename());
    if(settings.getAreMovesLimited()){
        command.append("-m ");
        command.append(std::to_string(settings.getLimitedMovesNumber()));
    }
    systemResult = system(command.c_str());

    //read the file
    if(systemResult==0) {
        ParseFile parse(settings, &game);
        parse.readGameFile();
    }
    else
        return 1;
    
    return 0;
}


