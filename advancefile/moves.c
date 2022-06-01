//
// Created by wendellbest on 5/31/22.
//
/** Movement rules:
 * STOCK: can only remove the top card and expose the next card in the waste.
 * Reseting the stock/waste back to stock counts as a move. One or three cards
 * can be turned over, but it has to be three when the rule says three. If there
 * isn't three cards to turn over in the stock, just turn over the remaining cards.
 * Cards from the tableaus or foundations can not be placed on the stock/waste.
 * Stock/waste reset can be limited or unlimited.
 *
 * FOUNDATION:
 * Must be in the order of clubs, diamonds, hearts, and spades. Cards can be
 * moved from stock/waste or tableaus to foundation, but no card can be removed
 * from foundation. Cards are placed in ascending order starting with the Ace.
 *
 * TABLEAU:
 * 7 columns, game starts with the number of cards matching the column # and the
 * top card turned face up. Cards can be moved from one column to another or the
 * foundation. When moving from the tableau col to another column, several cards
 * be removed if they can be stacked correctly in another column. Only kings can
 * be placed on empty tableau spots.
 *
 * OTHER RULES:
 * The input file has rules for number of cards to turn over (one or three) and also
 * sets how many times the stock/waste can be reset, either N times or unlimited.
 *
 * OTHER FLAGS:
 * Three switches for use with advance set the number of moves from N to infinity,
 * writing the game configuration to an output file, and printing to exchange format.
 *
 * ADVANCE:
 * Advance will parse a list of moves and determine if they are all legal. Depending
 * on the flags, it will output to stdout or to a file.
 * "." - Moves T (1 or 3) cards from stock to waste.
 * "r" - Resets the waste pile back to stock.
 * The card moves are in the form of source -> destination. Sources can be w and 1-7,
 * destinations can be f or 1-7.
 * Will need to also keep track of the number of lines so any errors can be identified
 * if a move is incorrect. Errors are either in formating or invalid moves. If spaces
 * are between the symbols for the move, formatting error, but if the move is not legal,
 * then invalid move.Also need to identify the move that is invalid by name and by
 * position number.
 *
 * OUTPUT:
 * Processed N moves, all valid - where N is number of moves made
 * Move M is illegal: (move) - where M represents the the number of moves up to the illegal
 * move.
 * only display the top three cards in the waste in human readable format*/
#include "moves.h"
#include "../checkfile/check.h"
#include "../checkfile/stockWaste.h"

int validSource(char c){
    switch(c){
        case 'w' : return 1;
        case '1' : return 1;
        case '2' : return 1;
        case '3' : return 1;
        case '4' : return 1;
        case '5' : return 1;
        case '6' : return 1;
        case '7' : return 1;
        default : return 0;
    }
}

int validDestination(char c){
    switch(c){
        case 'F' : return 1;
        case '1' : return 1;
        case '2' : return 1;
        case '3' : return 1;
        case '4' : return 1;
        case '5' : return 1;
        case '6' : return 1;
        case '7' : return 1;
        default : return 0;
    }
}
int validAction(char c){
    switch(c){
        case '.' : return 1; //move cards from waste
        case 'r' : return 1; //reset waste to stock
        default: return 0;
    }
}
int moves(FILE *input, int *line, int *moves, Rules *rules){
    char buffer[MAX_BUFFER];
    while(fgets(buffer, MAX_BUFFER, input)){
        *line = *line + 1;
        for(int i = 0; i < MAX_BUFFER; i++){
            if(validAction(buffer[i])){
                *moves = *moves + 1;
                if(buffer[i] == '.'){
                    if(doStockWasteCardTurnover(rules) == 0){
                        fprintf(stderr,"Move %d is illegal: %c\n", *moves, buffer[i]);
                        return 0;
                    }
                }
                else{
                    if(doStockWasteReset(rules) == 0){
                        fprintf(stderr,"Move %d is illegal: %c\n", *moves, buffer[i]);
                        return 0;
                    }
                }
            }
            else if(validSource(buffer[i])){}
        }
    }
    return 1;
}