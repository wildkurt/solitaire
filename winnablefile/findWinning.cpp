//
// Created by wendellbest on 1/22/23.
//

#include "findWinning.h"
/**This program will need to:
 * 1. Create a output file in the exchange format appended with a list of moves
 * 2. Invoke advance with the correct flags to see if move is valid
 *      a. The flag "-m N" needs to be updated if there is a limit on moves and sent to advance
 *      b. The flag "-o fileOuput" needs to be part of invocation
 *      c: The flag "-x" for exchange format is required to get the file back
 *      d. This is the same as the winnable switch
 * 3. Read the output file from advance into a new game configuration
 *      a. The output file from Advance will not have any moves. In this case, it
 *      would be possible to just append one move at a time to the input file for advance.
 *      Without the need to append all the moves, then the moves in the list of moves will
 *      only be the valid ones.
 * 4. Need to make sure to impliment the "-c" flag for a hash table
 * 5. "-f" for force moves to the foundation
 * 6. "-v" verbose mode, which is just sending notifications to the screen of numbers of
 * configurations checked*/



findWinning::findWinning(SearchSettings settings, gameConfiguration game): settings(settings), initialGame(game) {}

findWinning &findWinning::operator=(const findWinning &findb) {
    settings = findb.settings;
    return *this;
}

bool findWinning::winningGameSearch() {
    gameConfiguration temp = initialGame;
    return false;
}

bool findWinning::writeToAdvance(char rom, char tO, gameConfiguration configuration) {
    return false;
}
