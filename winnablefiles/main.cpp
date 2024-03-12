//
// Created by wendellbest on 2/29/24.
//
#include <iostream>
#include "winnable.h"

/**This program's purpose is to search for a winning combination of moves.
 * Switches:
 * -m N how many moves will be played or the default is 1000.
 * -c use a hash table
 * -f perform safe moves to the foundation
 * -v verbose mode
 * There will be only one file name that can be passed, must also drw from stdin
 * Must search for gaurunteed winnable situation:
 * -No covered cards
 * -No stock cards
 * -At most one waste card
 * - No need to search for moves that result in all cards in the foundations.
 * The search will be done by depth first search recursively.
 * - I believe the idea is to follow a path of valid moves until a winning configuration is found or the move limit
 * is reached.
 * Using a cache, is supposed to help in keeping repeated attempts at series of moves that don't result in a winning
 * configuration. I think what this means is that when searching for a valid move, you don't want to follow a invalid
 * one again. What does that mean?
 * Case 1: all the moves are valid but the move limit stops the search.
 * Case 2: None of the moves tested result in a valid next move.
 * The cache keeps track of the number of moves and the game configuration and then also provides the information that
 * when reaching X number of moves, there isn't anymore valid moves.
 * So, for each move, a entry is made in the hash table indicating whether a move was found to be valid or not. The
 * recursive program will look for an entry with the same move number and move and if valid, will proceed, if not, then
 * the recursion stops. So there will a need to track invalid moves based on the current number of moves made to create
 * the list. The hash function will need to retrieve information based on the number of moves and the particular move.
 * w->f = 1
 * col->f = 7
 * col->col = 42 because a move from the a col to the same col doesn't count. That eliminates 7 moves.
 * 50 possible moves. Two numbers, number of moves followed by the number of the move*/

int main(int args, char *argv[]){
    int movesSoFar = 0;
    //Creat a Winnable object
    Winnable winnable;
    //Get the command line arguments
    winnable.retrieveCommandLineArguments(args,argv);
    /*get the game from the file and also run advance and check. Running advance allows Advance to create a file for use
     * by check to perform the check. This is done to retrieve the contents of stdin and make sure it is put into a file
     * that can be accessed by the calling. If it isn't done this way, check would empty the stdin buffer and there would
     * be no input for advance since check doesn't output the game configuration. Winnable also requires access to the file*/
    if(!winnable.getAndCheckGameFile()){
        exit(1);
    }
    if(!winnable.searchForWinningSeriesOfMoves(&movesSoFar)){
        std::cerr << "# Game is not winnable in " << winnable.getMovestoPlay() << std::endl;
        exit(1);
    }
    //Print the command line arguments for testing
    winnable.printWinnableCLIArguments();
    //print the game configuration for testing
    winnable.printGameConfiguration();
    return 0;
}