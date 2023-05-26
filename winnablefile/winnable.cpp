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
    std::string command = "/home/wendellbest/Documents/my-c-and-c-plus-plus-projects/Solitaire/cmake-build-debug/advance -x -o output.txt ";
    //get the settings
    settings.getSettingsFromCL(argc, argv);
    //use advance to check the file
    command.append(settings.getFilename());
    system(command.c_str());
    //read the file
    ParseFile parse(settings, &game);
    parse.readGameFile();


    return 0;
}


