//
// Created by wende on 5/30/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include "../commonfiles/gameconfiguration.h"
#include "check.h"

/** The main program will open the file then parse it to find all
 * the required elements. During parsing, it calls functions that
 * will determine if there is a element present and will also
 * check the tableaus for a legal order. Foundations will be checked
 * for correct suits. It will then initiate a count of covered cards
 * and cards in the stock and waste*/

int main(int args, char *argv[]){
    //Create a place to put the game
    GameConfiguration game = {.rules ={.cardTurnover = 0, .wasteResets = 0}, .foundation = {.foundation = {0}},
                              .tableau = {.tab1 = {0}, .tab2 = {0}, .tab3 = {0}, .tab4 = {0}, .tab5 = {0}, .tab6 = {0},
                              .tab7 = {0}}, .stockwaste = {0}};
    //get the game file
    if(!getGameFile(&game, argv[1])){
        exit(1);
    }
    printRules(&game.rules);
}
