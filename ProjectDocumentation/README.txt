Switches -

switch                                                 check advance winnable game
-m N           *at most N moves played from game file            X       X
-o <filename>  *output file name                                 X
-x             *output game in exchange format                   X
-c             *Use a hashtable                                          X
-f             *Force safe moves to foundation                           X
-v             *verbose mode                                             X
-f <filename>  *File to get game configuration from                             X
-s <seed>      *Initialize the game with a seed                                 X
-1             *Turn one card over                                              X
-3             *Turn 3 cards over                                               X
-l <L>         *L is the number of waste resets                                 X

check: All it is doing is checking the game configuration to see if it is valid.
Correct number of cards, tableau order correct.

advance: uses check to verify file is correct, then checks if the moves are all
valid.

winnable: uses advance to find valid moves.

game: is the gui in a terminal window

Keeping track of moves. For advance, it limits how many of the moves it
can check, so if the move limit is reached, it stops even if there are more moves.
Winnable just specifies how many moves max can be played.
