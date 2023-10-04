//
// Created by wendellbest on 3/18/23.
//

#include "SearchSettings.h"
#include "parseFile.h"

int main(int argc, char **argv){
    SearchSettings settings;
    GameConfiguration game;

    //get the settings
    settings.getSettingsFromCL(argc, argv);
    //Check the file and retrieve the game if valid
    if(game.checkGameFile(&settings))
        game.getInputFile(&settings);
    else
        return 1;
    if(game.isWinnable(&settings)){}
    else{}
    return 0;
}
