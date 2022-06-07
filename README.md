# Solitaire
When I was taking Advanced Programming this was the semester long project. It had four parts, the first two were to be written in C and the last two in C++.
The first two are executables "check" which makes sure the exchange file is correct and "advance" that checks to see if the moves in the file are valid.
The next two are "winnable" and "game" with "winnable" performing a search for a list of moves that result in a winning configuration and "game" providing 
a playable user interface. I am still working on parts 3 and 4.

The project documentation is the documents provided during the class. I am making sure I can meet all the requirements. Right now I am documenting in the code, but will later add additional documentation when I get closer to finalizing things.

If you want to run the code, make sure to run it on a Linux machine as running under windows causes some of the file parsing to skip parts of the line. I have yet to figure out why. I have a Makefile, which is usually updated for compiling the code. It's a pretty good implimentation so if there is a missing dependency just update it and then it should compile just fine. You can also just compile the individual parts, but to run "advance" you'll need to have "check" and basicly the 2-4 executables rely on the previous executable.
