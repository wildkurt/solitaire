CHECK:
This program is based off of the part1.pdf.
It basically makes sure the file format is correct.
Counts the cards to look for missing cards, extra cards, or duplicates.
Makes sure the Tableau is correct as well.

check.c is the main program. It gets the filename
from the command line then opens the file. It then
starts going through the file line by line looking
for keywords and keeping track of when a key word is
found. This will make sure the format is correct
in regards to the headings. As for the sections of the
file that contain the cards, when the heading for
FOUNDATIONS:, TABLEAU:, and STOCK: are encountered
then functions are called to get the cards.

The buffer used to get each line fo the file is zeroed out
to remove the contents of the previous buffer.

The next step is to call the function to look for
missing and duplicate cards.

If the file is valid, it will print the results by
counting the cards and printing the counts out.

ADVANCE:
This program is based off of the part2.pdf.
This program also retrieves command line flags and filenames.
It uses the "check" program to confirm the file is valid, if so, then
it can read the file without the need to check the format, but
is still looking for the headings to trigger the functions for
getting the cards. This program also uses some of the functions
from check to read the file in, then has additional code that
reads the list of moves at the bottom of the file and determine
if the moves are legal.

WINNABLE:
This program is based off of the part3.pdf.
winnable.cpp is the main program.
Made a class parseGameFile that is dedicated to getting the game from
the game file.
The game goes in to a gameConfiguration which has objects for the
rules, foundation, tableau, stock/waste, and moves.

GAME:
This program is based off of the part4.pdf.