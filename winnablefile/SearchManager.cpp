//
// Created by wendellbest on 5/25/23.
//

#include "SearchManager.h"
SearchManager::SearchManager(GameConfiguration *gam, SearchSettings set) {
    game = gam;
    settings = set;
}

bool SearchManager::run() {
    GameConfiguration recursiveGame;
    recursiveGame = *game;
    if(recursiveSearch(recursiveGame))
        return true;
    else
        return false;
}

bool SearchManager::recursiveSearch(GameConfiguration recGame) {
    //check for winning condition
    if(recGame.gameInWinningConfiguration()){
        *game = recGame;
        return true;
    }
    if(settings.getAreMovesLimited()){
        if(recGame.getCurrentNumberOfMoves() >= settings.getLimitedMovesNumber())
            return false;
    }
    if(recGame.getRuleLimitedWasteResets()){
        if(recGame.getCurrentWasteResets() >= recGame.getRuleLimitedWasteNumber()){
            return false;
        }
    }
    if(settings.doVerboseMode()){

    }
    //Updating number of configurations
    configurations++;

    for(int i = 0; i < cardFrom.size(); i++){
        for(int j = 0; j < cardTo.size(); j++){
            //Don't check if from and to are the same index
            if(cardFrom[i] == cardTo[j]){
                continue;
            }
            else{
                /* 1. Check For Safe Moves
                 * 2. If cache mode is selected, create hash of moves including new one
                 *      a. Check hash table
                 *      b. If it exists, continue (copy over the one that exists with current move)
                 *      c. If it doesn't exist, test new move
                 * 4. Things to update or check:
                 *  a. Number of moves, and determine if more moves remain
                 *      a1. Moves are in a vector, so size of vector is number of moves
                 *  b. Number of configurations
                 *  c. remaining waste resets*/
                //Check for safe moves for every tested move
                if(settings.doSafemoves()){
                   /* A card can be moved to the foundation if the rank of the card with the same suit in the foundation
                    * has the same rank as the cards in the opposite color columns. If the rule is 3 card turn over, can
                    * only look at columns.
                    * 1. Need to get the value of a card in waste or columns, unless three card draw then only columns
                    * 2. See if the card the next rank lower is on the foundation
                    * 3. Check the opposite colors to make sure the rank is equal to the rank of the suit of the card
                    * in the waste or columns we are currently checking
                    * 4. If true, then add the move and test it, if not, then do nothing*/
                   int from = recGame.CanDoSafeMoves();
                   if(from != -1){
                       Move temp(cardFrom[from], cardTo[7]);
                       recGame.addMove(temp);
                       if(testGameConfiguration(recGame))
                           recursiveSearch(recGame);
                       else{
                           return false;
                       }
                   }
                }
                //Declaring a move
                Move temp;
                //Checking for card turn over and waste reset move
                if(cardFrom[i] == '.' || cardFrom[i] == 'r')
                    temp = Move (cardFrom[i], '0');
                else
                    temp = Move(cardFrom[i], cardTo[j]);
                //Add move to the game configuration
                recGame.addMove(temp);
                //What to do if a hash table is required
                if(settings.useAHashtable()){
                    int hashIndex = recGame.getConfigurationHash();
                    if(hashtable.count(hashIndex)>0){
                        //The hashtable entry already exists, so replace the entry
                        hashtable.insert({hashIndex, recGame});
                        //continue searching, no need to test
                        recursiveSearch(recGame);
                    }
                    else{
                        //If it isn't in the table, then insert
                        hashtable.insert({hashIndex, recGame});
                    }
                }

            }
        }
    }
    return false;
}

bool SearchManager::testGameConfiguration(GameConfiguration configuration) {
    /* 1. Create a file for advance to read
     * 2. use popen in read mode to read input from advance
     * 3. If it is a good move, return true*/
    std::string filename = "inputFile.txt";
    std::ofstream testFile;
    testFile.open(filename);
    configuration.printRules(&testFile);
    configuration.printFoundations(&testFile);

    return false;
}
