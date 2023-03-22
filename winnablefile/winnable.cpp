//
// Created by wendellbest on 3/18/23.
//
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "SearchSettings.h"
#include "parseFile.h"

int main(int argc, char **argv){
    std::string adinput = "adinput.txt";
    std::string adoutput = "adoutput.txt";
    std::string systemCommand = "~/Documents/my-c-and-c-plus-plus-projects/Solitaire/cmake-build-debug/advance adinput.txt -x -o adoutput.txt";
    SearchSettings settings;
    settings.getSettingsFromCL(argc,argv);
    GameConfiguration game;
    ParseFile pfile(settings, &game);
    if(!pfile.readGameFile())
       std::cerr << "Unable to open " << settings.getFilename() << std::endl;
    if(!pfile.writeGameFile(adinput))
        std::cerr << "Unable to open" << adinput << std::endl;
    system(systemCommand.c_str());
    return 0;
}


