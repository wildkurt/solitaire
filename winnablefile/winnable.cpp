//
// Created by wendellbest on 3/18/23.
//
#include <iostream>
#include <fstream>
#include "SearchSettings.h"
#include "parseFile.h"

int main(int argc, char **argv){
   SearchSettings settings;
   settings.getSettingsFromCL(argc,argv);
   GameConfiguration game;
   ParseFile pfile(settings, game);
   pfile.readGameFile();

   return 0;
}


